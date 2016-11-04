#pragma once

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget

{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();

protected: 
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

};

#endif // GLWIDGET_H