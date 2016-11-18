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
	//add actions

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
}

void MainWindow::import()
{

}

void MainWindow::exportM()
{

}

void MainWindow::about()
{

}

void MainWindow::exit()
{

}