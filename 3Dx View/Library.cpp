#include "Library.h"
#include <iterator>



Library::Library()
{
}


Library::~Library()
{
}

template <typename T>
int ArraySize(T* tmp) {
	return sizeof(tmp) / sizeof(*tmp);
}

Object3D Library::Import(string str)
{	
	char*name = new char[str.length() + 1];
	strcpy(name, str.c_str());
	C_Object3D c_obj = Imp(name);
	Object3D obj = StructToClass(c_obj);
	return obj;
}

bool Library::Export(Object3D obj) {
	
	C_Object3D c_obj = ClassToStruct(obj);

	Exp(c_obj);
	return 0;	//if did not fail
}

string Library::GetName()
{
	return name;
}

bool Library::Exp(C_Object3D)
{
	return false;
}

Library::C_Object3D Library::Imp(char *)
{
	return C_Object3D();
}

Object3D Library::StructToClass(const C_Object3D & c_obj)
{
	/*
	Algortym:
	z tablicy na array:
	dlugosc tablicy
	tworzenie pustego wektora struktur
	dodawanie elementow tablicy do wektorow struktur
	konwersja wektorow struktur na wektory klas (UNIF!)
	*/

	int facesArraySize = ArraySize(c_obj.faces);
	int uvArraySize = ArraySize(c_obj.uv);
	int normalsArraySize = ArraySize(c_obj.normals);
	int verticesArraySize = ArraySize(c_obj.vertices);

	vector<C_Face>		tmpC_Faces;
	vector<C_Vertex>	tmpC_Uv;
	vector<C_Vertex>	tmpC_Normals;
	vector<C_Vertex>	tmpC_Vertices;

	for (int i = 0; i < facesArraySize; i++) {
		tmpC_Faces.push_back(c_obj.faces[i]);
	}
	for (int i = 0; i < uvArraySize; i++) {
		tmpC_Uv.push_back(c_obj.uv[i]);
	}
	for (int i = 0; i < normalsArraySize; i++) {
		tmpC_Normals.push_back(c_obj.normals[i]);
	}
	for (int i = 0; i < verticesArraySize; i++) {
		tmpC_Vertices.push_back(c_obj.vertices[i]);
	}

	vector<Face>	tmp_Faces;
	vector<Vertex>	tmp_Uv;
	vector<Vertex>	tmp_Normals;
	vector<Vertex>	tmp_Vertices;

	for each (C_Vertex var in tmpC_Vertices)
	{
		Vertex tmp;
		tmp.x = var.x;
		tmp.y = var.y;
		tmp.z = var.z;
		tmp_Vertices.push_back(tmp);
	}

	for each (C_Vertex var in tmpC_Normals)
	{
		Vertex tmp;
		tmp.x = var.x;
		tmp.y = var.y;
		tmp.z = var.z;
		tmp_Normals.push_back(tmp);
	}

	for each (C_Vertex var in tmpC_Uv)
	{
		Vertex tmp;
		tmp.x = var.x;
		tmp.y = var.y;
		tmp.z = var.z;
		tmp_Uv.push_back(tmp);
	}

	for each (C_Face var in tmpC_Faces)
	{
		Point *first = &var.first;
		Point *second = &var.second;
		Point *third = &var.third;
		Face tmp(first, second, third);
		tmp_Faces.push_back(tmp);
	}
	
	Object3D obj;
	obj.faces = tmp_Faces;
	obj.normals = tmp_Normals;
	obj.uvs = tmp_Uv;
	obj.vertices = tmp_Vertices;

	return obj;
}

Library::C_Object3D Library::ClassToStruct(const Object3D &obj)
{
	/*
	Algorytm
	z wektora na tablice:
	stworzenie wektorow struktur
	konwersja z wektorow klas na wektory struktur
	przypisanie
	*/

	C_Object3D c_obj;
	
	vector<C_Face>		tmpFaces;
	vector<C_Vertex>	tmpUv;
	vector<C_Vertex>	tmpNormals;
	vector<C_Vertex>	tmpVertices;
	for each (Vertex var in obj.vertices)
	{
		C_Vertex tmp;
		tmp.x = var.x;
		tmp.y = var.y;
		tmp.z = var.z;
		tmpVertices.push_back(tmp);
	}

	for each (Vertex var in obj.normals)
	{
		C_Vertex tmp;
		tmp.x = var.x;
		tmp.y = var.y;
		tmp.z = var.z;
		tmpNormals.push_back(tmp);
	}

	for each (Vertex var in obj.uvs)
	{
		C_Vertex tmp;
		tmp.x = var.x;
		tmp.y = var.y;
		tmp.z = var.z;
		tmpUv.push_back(tmp);
	}

	for each (Face var in obj.faces)
	{
		Point first = *var.first;
		Point second = *var.second;
		Point third = *var.third;
		C_Face tmp = { first,second,third };
		tmpFaces.push_back(tmp);

	}

	c_obj.faces = &tmpFaces[0];
	c_obj.vertices = &tmpVertices[0];
	c_obj.uv = &tmpUv[0];
	c_obj.normals = &tmpNormals[0];

	return c_obj;
}





 
