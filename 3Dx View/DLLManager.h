#pragma once
#include <vector>
#include <QDir>
#include <QString>
#include <boost/dll.hpp>
#include<boost/filesystem/path.hpp>

class DLLManager
{
private:
	boost::filesystem::path dir;
	std::vector<std::string> pluginList;

public:
	DLLManager(std::string);
	~DLLManager();

	std::size_t load_plugins();
};

