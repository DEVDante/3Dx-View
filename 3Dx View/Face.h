#pragma once

struct Point
{
	int vertexIndices;
	int vertexTexture;
	int normalIndices;

	Point(int vertexIndices, int vertexTexture, int normalIndices)
	{
		this->normalIndices = normalIndices;
		this->vertexIndices = vertexIndices;
		this->vertexTexture = vertexTexture;
	}

};

class Face
{
public:

	Point * first;
	Point * second;
	Point * third;

	Face(Point * first, Point * second, Point * third);
	~Face();
};

