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

private slots:
	void import();
	void exportM();
	void exit();
	void about();

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
	QAction *importAction;
	QAction *exportAction;
	QAction *exitAction;
	QMenu *optionsMenu;
	QMenu *infoMenu;
	QAction *aboutAction;

	void createActions();
};

#endif // MAINWINDOW_H