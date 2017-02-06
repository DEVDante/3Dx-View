#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QDir>
#include "mainwindow.h"
#include "PluginAPI.h"

std::vector<double> textToFloat(std::string txt) {
	std::string tmp = "";
	std::vector<double> tmp_vector;
	for (int i = 0; i < txt.length() + 1; i++) {
		if (txt[i] != ' ' && txt[i] != '/')
			tmp += txt[i];
		else if (tmp != "") {
			tmp_vector.push_back(std::stod(tmp.c_str()));
			tmp = "";
		}
	}
	tmp_vector.push_back(std::stod(tmp.c_str()));
	return tmp_vector;
}

Face textToInt(std::string txt) {

	//goraco pozdrawiam osobe ktora wymyslila by zamiast tablicy punktow dac trzy zmienne punkty
	//podobnie do struktury samego punktu...

	std::string tmp = "";
	Face tmp_face;
	Point *tmp_point = new Point(0, 0, 0);
	size_t n = std::count(txt.begin(), txt.end(), '/');
	int it_p = 0;
	int it_f = 0;
	bool pass = true;
	for (int i = 0; i < txt.length() + 1; i++) {
		{
			if (txt[i] == ' ' || i == txt.length()) {
				if (pass == false) {

					switch (it_p) {
					case 0:
						tmp_point->vertexIndices = std::stoi(tmp);
						break;
					case 1:
						if (tmp == "") {
							tmp = "0";
						}
						tmp_point->vertexTexture = std::stoi(tmp);
						break;
					case 2:
						tmp_point->normalIndices = std::stoi(tmp);
						break;
					}

					switch (it_f) {
					case 0:
						tmp_face.first = tmp_point;
						break;
					case 1:
						tmp_face.second = tmp_point;
						break;
					case 2:
						tmp_face.third = tmp_point;
						break;
					}
					it_f++;
				}
				pass = true;
				tmp_point = new Point(0, 0, 0);
				tmp = "";
				it_p = 0;
			}
			else if (txt[i] == '/') {
				switch (it_p) {
				case 0:
					tmp_point->vertexIndices = std::stoi(tmp);
					break;
				case 1:
					if (tmp == "") {
						tmp = "0";
					}
					tmp_point->vertexTexture = std::stoi(tmp);
					break;
				case 2:
					tmp_point->normalIndices = std::stoi(tmp);
					break;
				}
				it_p++;
				tmp = "";

			}

			else {
				tmp += txt[i];
				pass = false;
			}
		}
	}
	return tmp_face;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);
	layout = new QHBoxLayout();

	renderer = new GLWidget(this);
	//todo: create side panel

	layout->addWidget(renderer);
	//todo: add side panel to layout
	layout->setMargin(0);

	mainWidget->setLayout(layout);

	createActions();

	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(importAction);
	fileMenu->addAction(exportAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	optionsMenu = menuBar()->addMenu(tr("&Options"));
	optionsMenu->addSeparator()->setText(tr("Rendering mode"));
	optionsMenu->addAction(setWireframe);
	optionsMenu->addAction(setSmoothShaded);

	infoMenu = menuBar()->addMenu(tr("&Info"));
	infoMenu->addAction(aboutAction);

	setWindowTitle(tr("3Dx View"));
	setMinimumSize(600, 400);
	resize(1024, 768);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
	importAction = new QAction(tr("Import"), this);
	importAction->setShortcut(QKeySequence::Open);
	importAction->setStatusTip(tr("Import a 3D model"));
	connect(importAction, &QAction::triggered, this, &MainWindow::import);

	exportAction = new QAction(tr("Export"), this);
	exportAction->setShortcut(QKeySequence::Save);
	exportAction->setStatusTip(tr("Export current 3D model"));
	connect(exportAction, &QAction::triggered, this, &MainWindow::exportM);

	exitAction = new QAction(tr("&Exit"), this);
	exitAction->setShortcut(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Close application"));
	connect(exitAction, &QAction::triggered, this, &MainWindow::exit);

	aboutAction = new QAction(tr("About"), this);
	aboutAction->setShortcut(QKeySequence::HelpContents);
	aboutAction->setStatusTip(tr("About application"));
	connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

	renderMode = new QActionGroup(this);
	setWireframe = new QAction(tr("Wireframe"), renderMode);
	setWireframe->setCheckable(true);
	connect(setWireframe, &QAction::triggered, this, &MainWindow::wireframeMode);
	renderMode->addAction(setWireframe);

	setSmoothShaded = new QAction(tr("Smooth shaded"), renderMode);
	setSmoothShaded->setCheckable(true);
	setSmoothShaded->setChecked(true);
	connect(setSmoothShaded, &QAction::triggered, this, &MainWindow::sShadedMode);
	renderer->addAction(setSmoothShaded);
}

void MainWindow::import()
{
	QStringList filter("*.dll");
	QDir directory(QDir::currentPath());
	QStringList dllList = directory.entryList(filter);
	std::vector<boost::filesystem::path> plugins;
	for (int i = 0; i < dllList.length(); i++)
		plugins.push_back(QDir::currentPath().toStdString() + "/" + dllList[i].toStdString());

	boost::shared_ptr<PluginAPI> plugin;
	QString fileFilter = "";
	std::map<std::string, boost::filesystem::path> pluglist;

	for (int i = 0; i < plugins.size(); i++)
	{
		plugin = boost::dll::import<PluginAPI>(plugins[i], "plugin", boost::dll::load_mode::append_decorations);
		pluglist[plugin->name()] = plugins[i];
		fileFilter += QString::fromStdString(plugin->name()).toUpper() + " (*." + QString::fromStdString(plugin->name()) + ");;";
	}

	QString filename = QFileDialog::getOpenFileName(this, tr("Import model file"), QDir::currentPath(), fileFilter);

	if (filename != "")
	{
		plugin = boost::dll::import<PluginAPI>(pluglist[QFileInfo(filename).suffix().toStdString()], "plugin", boost::dll::load_mode::append_decorations);

		Model3D *mdl = new Model3D();
		std::ifstream file(filename.toStdString());
		if (file.is_open())
		{

			std::string text = "";
			std::string tmp = "";
			mdl->models.resize(1);


			file.clear();
			file.seekg(0, std::ios::beg);

			while (getline(file, text)) {
				tmp = text.substr(0, 2);
				if (tmp == "v ")
				{
					Vertex v;
					std::vector<double> wekt = textToFloat(text.substr(2, text.length()));
					v.x = wekt.at(0);
					v.y = wekt.at(1);
					v.z = wekt.at(2);
					mdl->models[0].vertices.push_back(v);
				}
				if (tmp == "vn")
				{
					std::vector<double> wekt = textToFloat(text.substr(2, text.length()));
					Vertex v;
					v.x = wekt.at(0);
					v.y = wekt.at(1);
					v.z = wekt.at(2);
					mdl->models[0].normals.push_back(v);
				}
				if (tmp == "f ")
				{
					Face f = textToInt(text.substr(2, text.length()));
					mdl->models[0].faces.push_back(f);
				}

			}

			file.close();
		}

		//renderer->model3D = (plugin->importM(filename.toStdString()));
		renderer->model3D = mdl;
		renderer->update();
	}
}

void MainWindow::exportM()
{
	QStringList filter("*.dll");
	QDir directory(QDir::currentPath());
	QStringList dllList = directory.entryList(filter);
	std::vector<boost::filesystem::path> plugins;
	for (int i = 0; i < dllList.length(); i++)
		plugins.push_back(QDir::currentPath().toStdString() + "/" + dllList[i].toStdString());

	boost::shared_ptr<PluginAPI> plugin;
	QString fileFilter = "";
	std::map<std::string, boost::filesystem::path> pluglist;

	for (int i = 0; i < plugins.size(); i++)
	{
		plugin = boost::dll::import<PluginAPI>(plugins[i], "plugin", boost::dll::load_mode::append_decorations);
		pluglist[plugin->name()] = plugins[i];
		fileFilter += QString::fromStdString(plugin->name()).toUpper() + " (*." + QString::fromStdString(plugin->name()) + ");;";
	}

	QString filename = QFileDialog::getSaveFileName(this, tr("Export model to file"), QDir::currentPath(), fileFilter);

	if (filename != "")
	{
		plugin = boost::dll::import<PluginAPI>(pluglist[QFileInfo(filename).suffix().toStdString()], "plugin", boost::dll::load_mode::append_decorations);

		plugin->exportM((renderer->model3D), filename.toStdString());
	}
}

void MainWindow::about()
{
	QMessageBox::information(this, tr("About"), tr("Info"));
}

void MainWindow::wireframeMode()
{
	renderer->changeRenderMode(GL_FRONT_AND_BACK, GL_LINE);
	renderer->update();
}

void MainWindow::sShadedMode()
{
	renderer->changeRenderMode(GL_FRONT_AND_BACK, GL_FILL);
	renderer->update();
}

void MainWindow::exit()
{
	QApplication::quit();
}