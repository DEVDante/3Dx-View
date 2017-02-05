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

std::vector<int> textToInt(std::string tmp) {
	std::string txt = "";
	std::vector<int> tmp_vector;
	for (int i = 0; i < tmp.length() + 1; i++) {
		if (tmp[i] == ' '  && txt != "")
		{
			tmp_vector.push_back(std::stoi(txt));
			txt = "";
		}
		else if (tmp[i] == '/')
		{
			if (txt == "")
				tmp_vector.push_back(0);
			else
				tmp_vector.push_back(std::stoi(txt));
			txt = "";
		}
		else {
			txt += tmp[i];
		}
	}
	tmp_vector.push_back(std::stod(tmp.c_str()));
	return tmp_vector;
}

namespace format {

	class plugname : public PluginAPI {	//zmienic nazwe klasy
		
	public:
		plugname() {

		}

		std::string name() const {
			return "obj";	//zwracac nazwe rozszerzenia
		}

		void exportM(Model3D, char* filename)
		{
			int n = 2;
		}

		Model3D importM(char* filename)
		{
			Model3D *mdl = new Model3D();
			std::ifstream file("C:\\cube.obj");
			if (file.is_open())
			{
				std::string text = "";
				std::string tmp = "";

				unsigned int count_o = 0;
				while (getline(file, text))
				{
					tmp = text.substr(0, 2);
					if (tmp == "o " || tmp == "g ")
					{
						count_o++;
					}
				}

				long int propIter = 0;

				if (count_o) {
					mdl->models.resize(count_o);
					propIter = -1;
				}
				else
					mdl->models.resize(1);



				file.clear();
				file.seekg(0, std::ios::beg);

				while (getline(file, text)) {
					tmp = text.substr(0, 2);
					if (tmp == "o " || tmp == "g ") {
						propIter++;
					}
					if (tmp == "v ")
					{
						Vertex v;
						std::vector<double> wekt = textToFloat(text.substr(3, text.length()));
						v.x = wekt.at(0);
						v.y = wekt.at(1);
						v.z = wekt.at(2);
						mdl->models[propIter].vertices.push_back(v);
					}
					if (tmp == "vn")
					{
						std::vector<double> wekt = textToFloat(text.substr(3, text.length()));
						Vertex v;
						v.x = wekt.at(0);
						v.y = wekt.at(1);
						v.z = wekt.at(2);
						mdl->models[propIter].normals.push_back(v);
					}
					if (tmp == "f ")
					{
						std::vector<int> wekt = textToInt(text.substr(2, text.length()));
						Face f;

						f.first = new Point((int)wekt.at(0), (int)wekt.at(1), (int)wekt.at(2));
						f.second = new Point((int)wekt.at(3), (int)wekt.at(4), (int)wekt.at(5));
						f.third = new Point((int)wekt.at(6), (int)wekt.at(7), (int)wekt.at(8));

						mdl->models[propIter].faces.push_back(f);
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