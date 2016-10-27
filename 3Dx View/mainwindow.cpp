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

	fileMenu = menuBar()->addMenu(tr("&File"));
	//add actions
	optionsMenu = menuBar()->addMenu(tr("&Options"));
	//add actions
	infoMenu = menuBar()->addMenu(tr("&Info"));
	//add actions

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
