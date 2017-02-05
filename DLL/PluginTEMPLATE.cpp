#include <boost\dll\alias.hpp> // for BOOST_DLL_ALIAS
#include <boost\make_shared.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include "PluginAPI.h"
#include "Model3D.h"

std::vector<double> textToFloat(std::string txt) {
	std::string tmp = "";
	std::vector<double> tmp_vector;
	for (int i = 0; i < txt.length() + 1; i++) {
		if (txt[i] != ' ' && txt[i] != '/')
			tmp += txt[i];
		else if (tmp != "") {
			tmp_vector.push_back(std::stod(tmp.c_str()));
			tmp = "";
		}
	}
	tmp_vector.push_back(std::stod(tmp.c_str()));
	return tmp_vector;
}

Face textToInt(std::string txt) {

	//goraco pozdrawiam osobe ktora wymyslila by zamiast tablicy punktow dac trzy zmienne punkty
	//podobnie do struktury samego punktu...

	std::string tmp = "";
	Face tmp_face;
	Point *tmp_point = new Point(0, 0, 0);
	size_t n = std::count(txt.begin(), txt.end(), '/');
	int it_p = 0;
	int it_f = 0;
	bool pass = true;
	for (int i = 0; i < txt.length() + 1; i++) {
		{
			if (txt[i] == ' ' || i == txt.length()) {
				if (pass == false) {

					switch (it_p) {
					case 0:
						tmp_point->vertexIndices = std::stoi(tmp);
						break;
					case 1:
						if (tmp == "") {
							tmp = "0";
						}
						tmp_point->vertexTexture = std::stoi(tmp);
						break;
					case 2:
						tmp_point->normalIndices = std::stoi(tmp);
						break;
					}

					switch (it_f) {
					case 0:
						tmp_face.first = tmp_point;
						break;
					case 1:
						tmp_face.second = tmp_point;
						break;
					case 2:
						tmp_face.third = tmp_point;
						break;
					}
					it_f++;
				}
				pass = true;
				tmp_point = new Point(0, 0, 0);
				tmp = "";
				it_p = 0;
			}
			else if (txt[i] == '/') {
				switch (it_p) {
				case 0:
					tmp_point->vertexIndices = std::stoi(tmp);
					break;
				case 1:
					if (tmp == "") {
						tmp = "0";
					}
					tmp_point->vertexTexture = std::stoi(tmp);
					break;
				case 2:
					tmp_point->normalIndices = std::stoi(tmp);
					break;
				}
				it_p++;
				tmp = "";

			}

			else {
				tmp += txt[i];
				pass = false;
			}
		}
	}
	return tmp_face;
}

namespace format {

	class plugname : public PluginAPI {	//zmienic nazwe klasy
		
	public:
		plugname() {

		}

		std::string name() const {
			return "obj";	//zwracac nazwe rozszerzenia
		}

		void exportM(Model3D, std::string)
		{
			int n = 2;
		}

		Model3D importM(std::string fname)
		{
			Model3D *mdl = new Model3D();
			std::ifstream file(fname);
			if (file.is_open())
			{

				std::string text = "";
				std::string tmp = "";
				mdl->models.resize(1);


				file.clear();
				file.seekg(0, std::ios::beg);

				while (getline(file, text)) {
					tmp = text.substr(0, 2);
					if (tmp == "v ")
					{
						Vertex v;
						std::vector<double> wekt = textToFloat(text.substr(3, text.length()));
						v.x = wekt.at(0);
						v.y = wekt.at(1);
						v.z = wekt.at(2);
						mdl->models[0].vertices.push_back(v);
					}
					if (tmp == "vn")
					{
						std::vector<double> wekt = textToFloat(text.substr(3, text.length()));
						Vertex v;
						v.x = wekt.at(0);
						v.y = wekt.at(1);
						v.z = wekt.at(2);
						mdl->models[0].normals.push_back(v);
					}
					if (tmp == "f ")
					{
						Face f = textToInt(text.substr(2, text.length()));
						mdl->models[0].faces.push_back(f);
					}

				}

				file.close();
			}
			return *mdl;
		}

		~plugname() {

		}

	};

	extern "C" BOOST_SYMBOL_EXPORT plugname plugin;
	plugname plugin;

} // namespace my_namespace