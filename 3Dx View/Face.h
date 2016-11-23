#pragma once

struct Point
{
	int vertexIndices;
	int vertexTexture;
	int normalIndices;
};

class Face
{
public:

	Point first;
	Point second;
	Point third;

	Face();
	~Face();
};

