#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include "GLWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	QWidget *mainWidget;
	GLWidget *renderer;
	QHBoxLayout *layout;

	//menus
	QMenuBar *mBar;
	QMenu *fileMenu;
	QMenu *optionsMenu;
	QMenu *infoMenu;
};

#endif // MAINWINDOW_H