#pragma once

#include <vector>
#include "Vertex.h"
#include "Face.h"

class Object3D
{
private: 

public:
	Object3D();
	~Object3D();

	std::vector<Vertex> vertices;
	std::vector<Vertex> normals;
	std::vector<Vertex> uvs;
	std::vector<Face> faces;

};