#include "GLWidget.h"

#include <gl/GLU.h>
#include<iostream>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	//timer.start(16);
	model3D = new Model3D;
	Object3D * object3D = new Object3D;

	object3D->vertices.push_back(*new Vertex(0.0, 0.0, 0.0));
	object3D->vertices.push_back(*new Vertex(0.0, 0.0, 1.0));
	object3D->vertices.push_back(*new Vertex(0.0, 1.0, 0.0));
	object3D->vertices.push_back(*new Vertex(0.0, 1.0, 1.0));
	object3D->vertices.push_back(*new Vertex(1.0, 0.0, 0.0));
	object3D->vertices.push_back(*new Vertex(1.0, 0.0, 1.0));
	object3D->vertices.push_back(*new Vertex(1.0, 1.0, 0.0));
	object3D->vertices.push_back(*new Vertex(1.0, 1.0, 1.0));

	object3D->normals.push_back(*new Vertex(0.0, 0.0, 1.0));
	object3D->normals.push_back(*new Vertex(0.0, 0.0, -1.0));
	object3D->normals.push_back(*new Vertex(0.0, 1.0, 0.0));
	object3D->normals.push_back(*new Vertex(0.0, -1.0, 0.0));
	object3D->normals.push_back(*new Vertex(1.0, 0.0, 0.0));
	object3D->normals.push_back(*new Vertex(-1.0, 0.0, 0.0));

	object3D->faces.push_back(*new Vertex(1.0, 7.0, 5.0));
	object3D->faces.push_back(*new Vertex(1.0, 3.0, 7.0));
	object3D->faces.push_back(*new Vertex(1.0, 4.0, 3.0));
	object3D->faces.push_back(*new Vertex(1.0, 2.0, 4.0));
	object3D->faces.push_back(*new Vertex(3.0, 8.0, 7.0));
	object3D->faces.push_back(*new Vertex(3.0, 4.0, 8.0));
	object3D->faces.push_back(*new Vertex(5.0, 7.0, 8.0));
	object3D->faces.push_back(*new Vertex(5.0, 8.0, 6.0));
	object3D->faces.push_back(*new Vertex(1.0, 5.0, 6.0));
	object3D->faces.push_back(*new Vertex(1.0, 6.0, 2.0));
	object3D->faces.push_back(*new Vertex(2.0, 6.0, 8.0));
	object3D->faces.push_back(*new Vertex(2.0, 8.0, 4.0));

	model3D->model.push_back(*object3D);
}

GLWidget::~GLWidget()
{
	delete model3D;
}

void GLWidget::initializeGL()
{
	glClearColor(0, 0, 0, 1);//ustawia kolor t³a
	glEnable(GL_DEPTH_TEST); //w³¹cza updateowanie bufora g³êbokoœci (wymagane jeszcze maska g³êbokoœci i bufor g³êbokoœci)
	glEnable(GL_LIGHT0); //typ œwiat³a
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

void GLWidget::drawTriangles(Object3D * object)
{
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < object->faces.size(); i++)
	{
		int index = (int)object->faces[i].x -1;
		Vertex v = object->vertices[index];
		glVertex3d(v.x, v.y, v.z);

		index = (int)object->faces[i].y -1;
		v = object->vertices[index];
		glVertex3d(v.x, v.y, v.z);

		index = (int)object->faces[i].z -1;
		v = object->vertices[index]; 
		glVertex3d(v.x, v.y, v.z);
	}
	glEnd();
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyœci bufory
	glMatrixMode(GL_MODELVIEW); //wypiera obecnie urzywany typ macierzy (do niego bed¹ siê odnosiæ kolejne polecenia)
	glLoadIdentity(); // to samo co glLoadMatrix
	gluLookAt(4, 3, 5, 0, 0, 0, 1, 0, 0); //eye XYZ, centerXYZ, upXYZ(not parallel to line from eye to reference point
	glColor3f(1, 1, 10);
	//glRotatef(angle, 0, 1, 1);
	//angle+=10;
	drawTriangles(&(model3D->model[0]));
}