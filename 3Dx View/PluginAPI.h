#pragma once
#include <boost/dll/import.hpp> // for import_alias
#include <boost/make_shared.hpp>
#include <boost/function.hpp>
#include <iostream>

struct vert
{
	/*pos - v
	normals - vn
	vt - text*/
	float pos[3];
};

struct norm
{
	/*pos - v
	normals - vn
	vt - text*/
	float pos[3];
};

struct text
{
	/*pos - v
	normals - vn
	vt - text*/
	float pos[2];
};

struct face 
{
	unsigned int vertsindices[3];
	unsigned int normindices[3];
	unsigned int textsindices[3];
};

struct prop 
{
	char* name;		//nazwy obiektow, pominac grupy
	char* matname;	//usemtl
	unsigned long int vertcount;	//ilosc vertow
	unsigned long int facecount;	//ilosc faceow

	struct vert *verts;
	struct norm *norms;
	struct text *texts;
	struct face *faces;
};

struct model
{
	unsigned int propcount;	//ilosc obiektow w modelu
	char* matlib;	//mtllib

	struct prop *props;
};

class PluginAPI {
public:
	virtual std::string name() const = 0;		//nazwa obslugiwanego formatu
	virtual void exportM(struct model, char* filename) = 0;
	virtual struct model importM(char* filename) = 0;
	virtual ~PluginAPI() {}
};

std::vector<std::pair<std::string, std::string>> get_plugin_list(const std::vector<boost::filesystem::path>& plugins);
void get_all(const boost::filesystem::path& root, const std::string& ext, std::vector<boost::filesystem::path>& ret);