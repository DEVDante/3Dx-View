#include "PluginAPI.h"
#include <vector>
#include <string>

namespace dll = boost::dll;

std::vector<std::pair<std::string, std::string>> get_plugin_list(const std::vector<boost::filesystem::path>& plugins) {
	std::vector<std::pair<std::string, std::string>> plugins_found;

	for (std::size_t i = 0; i < plugins.size(); ++i) {
		dll::shared_library lib(plugins[i], dll::load_mode::append_decorations);
		if (!lib.has("dx3init")) {
			// not compatible dll
			continue;
		}

		typedef boost::shared_ptr<PluginAPI>(pluginapi_create_t)();
		boost::function<pluginapi_create_t> creator = dll::import_alias<pluginapi_create_t>(boost::move(lib), "dx3init");
		plugins_found.push_back(std::pair<std::string, std::string>(plugins[i].string(), creator()->name()));
	}

	return plugins_found;
}

void get_all(const boost::filesystem::path& root, const std::string& ext, std::vector<boost::filesystem::path>& ret)
{
	if (!boost::filesystem::exists(root) || !boost::filesystem::is_directory(root)) return;

	boost::filesystem::recursive_directory_iterator it(root);
	boost::filesystem::recursive_directory_iterator endit;

	while (it != endit)
	{
		if (boost::filesystem::is_regular_file(*it) && it->path().extension() == ext) ret.push_back(it->path().filename());
		++it;

	}

}