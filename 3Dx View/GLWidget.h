#pragma once

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <qtimer.h>
#include"Model3D.h"

class GLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();
	int angle=0;
	QTimer timer;

protected: 
	void drawTriangles(Object3D * object);
	Model3D * model3D;
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
};

#endif // GLWIDGET_H