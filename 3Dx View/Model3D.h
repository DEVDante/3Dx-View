#pragma once

#include <vector>
#include "Object3D.h"

class Model3D
{
private: 

public:
	std::vector<Object3D> models;

	Model3D();
	~Model3D();
};

