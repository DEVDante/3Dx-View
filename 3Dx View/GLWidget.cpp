#include "GLWidget.h"

#include <gl/GLU.h>
#include<iostream>
#include <QPainter>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
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

	object3D->faces.push_back(*new Face(new Point(1, 0, 2), new Point(7, 0, 2), new Point(5, 0, 2)));
	object3D->faces.push_back(*new Face(new Point(1, 0, 2), new Point(3, 0, 2), new Point(7, 0, 2)));
	object3D->faces.push_back(*new Face(new Point(1, 0, 6), new Point(4, 0, 6), new Point(3, 0, 6)));
	object3D->faces.push_back(*new Face(new Point(1, 0, 6), new Point(2, 0, 6), new Point(4, 0, 6)));
	object3D->faces.push_back(*new Face(new Point(3, 0, 3), new Point(8, 0, 3), new Point(7, 0, 3)));
	object3D->faces.push_back(*new Face(new Point(3, 0, 3), new Point(4, 0, 3), new Point(8, 0, 3)));
	object3D->faces.push_back(*new Face(new Point(5, 0, 5), new Point(7, 0, 5), new Point(8, 0, 5)));
	object3D->faces.push_back(*new Face(new Point(5, 0, 5), new Point(8, 0, 5), new Point(6, 0, 5)));
	object3D->faces.push_back(*new Face(new Point(1, 0, 4), new Point(5, 0, 4), new Point(6, 0, 4)));
	object3D->faces.push_back(*new Face(new Point(1, 0, 4), new Point(6, 0, 4), new Point(2, 0, 4)));
	object3D->faces.push_back(*new Face(new Point(2, 0, 1), new Point(6, 0, 1), new Point(8, 0, 1)));
	object3D->faces.push_back(*new Face(new Point(2, 0, 1), new Point(8, 0, 1), new Point(4, 0, 1)));

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

void drawFaces(Object3D * object, int vIdx, int vnIdx, int txIdx = 0)
{
	Vertex v = object->normals[vnIdx - 1];
	glNormal3d(v.x, v.y, v.z);

	v = object->vertices[vIdx - 1];
	glVertex3d(v.x, v.y, v.z);
}

void GLWidget::drawTriangles(Object3D * object)
{
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < object->faces.size(); i++)
	{
		Point * point = object->faces[i].first;
		drawFaces(object, point->vertexIndices, point->normalIndices);

		point = object->faces[i].second;
		drawFaces(object, point->vertexIndices, point->normalIndices);

		point = object->faces[i].third;
		drawFaces(object, point->vertexIndices, point->normalIndices);
	}
	glEnd();
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyœci bufory
	glMatrixMode(GL_MODELVIEW); //wypiera obecnie urzywany typ macierzy (do niego bed¹ siê odnosiæ kolejne polecenia)
	glLoadIdentity(); // to samo co glLoadMatrix
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 1, 0, 0); //eye XYZ, centerXYZ, upXYZ(not parallel to line from eye to reference point
	glColor3f(1, 1, 10);
	glPolygonMode(faceType, faceRenderMode);
	glRotatef(xRot + angleX, 1, 0, 0);
	glRotatef(yRot + angleY, 0, 1, 0);
	drawTriangles(&(model3D->model[0]));

	/*QPainter painter(this);
	painter.setPen(Qt::white);
	painter.setFont(QFont("Arial", 12));

	float x = countDistance();
	std::string s = std::to_string(x);
	painter.drawText(30, 20, "distance");
	painter.drawText(30, 40, tr(s.c_str()));
	s = std::to_string(zoom);
	painter.drawText(30, 60, "zoom");
	painter.drawText(30, 80, tr(s.c_str()));

	painter.end();*/
}

void GLWidget::changeRenderMode(GLenum face, GLenum mode)
{
	faceType = face;
	faceRenderMode = mode;
}

void GLWidget::mousePressEvent(QMouseEvent * event)
{
	posX = event->x();
	posY = event->y();
	angleX = 0;
	angleY = 0;
}

void GLWidget::mouseMoveEvent(QMouseEvent * event)
{
	angleX = ((float)(event->x() - posX)/10);
	angleY = (posY - (float)event->y())/10;
	update();
}

void GLWidget::mouseReleaseEvent(QMouseEvent * event)
{
	xRot += angleX;
	yRot += angleY;
	angleX = 0;
	angleY = 0;
}

float GLWidget::countSpeed(float x)
{
	if (x != 0)
		return -norm / x;
	else return 0;
}

void GLWidget::wheelEvent(QWheelEvent * event)
{
	delta = event->delta();
	zoom = (delta / 100);
	
	eyeX = normZoom(eyeX,centerX);
	eyeY = normZoom(eyeY, centerY);
	eyeZ = normZoom(eyeZ, centerZ);

	update();
}

float GLWidget::countDistance()
{
	return (sqrt(pow((eyeX - centerX), 2) + pow((eyeY - centerY), 2) + pow((eyeZ - centerZ), 2)))/5;
}

float GLWidget::normZoom(float eye, float center)
{
	float tmp = eye + zoom;
	if (tmp > center) return tmp;
	else return center;
}
