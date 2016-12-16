#include "DLLManager.h"

DLLManager::DLLManager(std::string directory = "dll/")
{
	dir = directory;
}

DLLManager::~DLLManager()
{
}

std::size_t DLLManager::load_plugins()
{
	std::size_t plugins_found = 0;
	QDir list(dir.generic_string().c_str(), "*.dll", QDir::NoSort, QDir::Files);
	QStringList dllList = list.entryList();

	return plugins_found; 
	return 15;
}
