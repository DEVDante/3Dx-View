#pragma once

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <qtimer.h>
#include "Model3D.h"

class GLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	int angle = 0;

	GLWidget(QWidget *parent = 0);
	~GLWidget();
	void changeRenderMode(GLenum, GLenum);


protected: 
	GLenum faceType = GL_FRONT_AND_BACK; //might be possible to change in OpenGL >3.0
	GLenum faceRenderMode = GL_FILL;
	Model3D * model3D;

	void drawTriangles(Object3D * object);
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
};

#endif // GLWIDGET_H