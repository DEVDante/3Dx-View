#include <QMessageBox>
#include <QApplication>
#include "mainwindow.h"

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
	delete renderer;
	delete layout;
	delete mainWidget;

	delete mBar;
	delete fileMenu;
	delete importAction;
	delete exportAction;
	delete exitAction;
	delete optionsMenu;
	delete renderMode;
	delete infoMenu;
	delete aboutAction;
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
}

void MainWindow::sShadedMode()
{
	renderer->changeRenderMode(GL_FRONT_AND_BACK, GL_FILL);
}

void MainWindow::exit()
{
	QApplication::quit();
}