#pragma once

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QtGui/QMouseEvent>
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

	float angleX = 0, angleY = 0;
	float xRot = 0.0f, yRot = 0.0f;
	float posX = 0, posY = 0;

	float eyeX = 3.0f, eyeY = 4.0f, eyeZ = 5.0f;
	float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;


protected: 
	GLenum faceType = GL_FRONT_AND_BACK; //might be possible to change in OpenGL >3.0
	GLenum faceRenderMode = GL_FILL;
	Model3D * model3D;

	void drawTriangles(Object3D * object);
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);

};

#endif // GLWIDGET_H