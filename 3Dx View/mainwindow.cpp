#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QDir>
#include "mainwindow.h"
#include "PluginAPI.h"

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
	for (int i = 0; i < plugins.size(); i++)
	{
		plugin = boost::dll::import<PluginAPI>(plugins[i], "plugin", boost::dll::load_mode::append_decorations);
		fileFilter += QString::fromStdString(plugin->name()).toUpper() + " (*." + QString::fromStdString(plugin->name()) + ");;";
	}

	QString filename = QFileDialog::getOpenFileName(this, tr("Import model file"), QDir::currentPath(), fileFilter);

	struct model test = plugin->importM("");
}

void MainWindow::exportM()
{

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