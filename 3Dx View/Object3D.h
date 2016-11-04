#pragma once

#include <vector>
#include "Vertex.h"

class Object3D
{
private: 
	std::vector<Vertex> vertices;
	std::vector<Vertex> normals;
	std::vector<Vertex> uvs;
	std::vector<Vertex> faces;

public:
	Object3D();
	~Object3D();
};

