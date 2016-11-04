#include "GLWidget.h"
#include <gl/GLU.h>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
	glClearColor(0, 0, 0, 1);//ustawia kolor t�a
	glEnable(GL_DEPTH_TEST); //w��cza updateowanie bufora g��boko�ci (wymagane jeszcze maska g��boko�ci i bufor g��boko�ci)
	glEnable(GL_LIGHT0); //typ �wiat�a
	glEnable(GL_LIGHTING); //If enabled and no vertex shader is active, use the current lighting parameters to compute the vertex color or index
	glEnable(GL_COLOR_MATERIAL); //glColorMaterial

}

void GLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / h, 0.01, 100);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czy�ci bufory
	glMatrixMode(GL_MODELVIEW); //wypiera obecnie urzywany typ macierzy (do niego bed� si� odnosi� kolejne polecenia)
	glLoadIdentity(); // to samo co glLoadMatrix
	gluLookAt(0, 0, 5, 0, 0, 0, 1, 0, 0); //eye XYZ, centerXYZ, upXYZ(not parallel to line from eye to reference point

	glColor3f(1, 1, 10);
	gluSphere(gluNewQuadric(), 1, 30, 30);
}
