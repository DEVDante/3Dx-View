#pragma once
#include "Object3D.h"
#include <string>

using namespace std;


class Library
{
public:
	Library();
	~Library();
	Object3D Import(string);
	bool Export(Object3D);
	string GetName();

protected:
	struct C_Vertex {
		double x;
		double y;
		double z;
	};
	struct C_Face {
		Point first;
		Point second;
		Point third;
	};
	struct C_Object3D {
		C_Face		*faces;
		C_Vertex	*normals;
		C_Vertex	*uv;
		C_Vertex	*vertices;
	};	
	bool		Exp(C_Object3D);
	C_Object3D	Imp(char*);	
	char*		GetNameChar();

private:
	string name="";			
	Object3D StructToClass(const C_Object3D&);
	C_Object3D ClassToStruct(const Object3D&);


};

/*
EXP i IMP to funkcje wczytywane z DLL
*/

