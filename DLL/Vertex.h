#pragma once

class Vertex
{
private: 

public:
	double x;
	double y;
	double z;

	Vertex(double x, double y, double z);
	Vertex(); // potrzebowalem do stworzenia vektora pelnego pustych vektorow
	~Vertex();
};

