#include "Face.h"

Face::Face()
{
}

Face::Face(Point * first, Point * second, Point * third)
{
	this->first = first;
	this->second = second;
	this->third = third;
}

Face::~Face()
{
}
