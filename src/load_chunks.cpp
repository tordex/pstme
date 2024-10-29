#include "load_chunks.h"
#include <filesystem>
#include <fstream>
#include "tools.h"

namespace fs = std::filesystem;


std::shared_ptr<chunks> load_bookmarks_from_file(const std::string &path)
{
	if(!fs::exists(path)) return {};

	std::ifstream infile(path);
	if(!infile.is_open()) return {};

	std::string bookmarks_name;

	std::getline(infile, bookmarks_name);
	if(bookmarks_name.empty()) return {};

	auto ret = std::make_shared<chunks>(bookmarks_name);

	// Search for --
	bool found_start = false;
	for(std::string line; std::getline(infile, line);)
	{
		if(line == "--")
		{
			found_start = true;
			break;
		}
	}
	if(!found_start) return {};
	for(std::string line; std::getline(infile, line);)
	{
		if(line.empty()) break;

		auto b = std::make_shared<chunk>(line);
		std::string tags;
		std::getline(infile, tags);
		auto tokens = split_string(tags, ";");
		for(auto& tok : tokens)
		{
			b->add_tag(trim(tok, " "));
		}
		for(std::string ln; std::getline(infile, ln);)
		{
			if(ln == "--") break;
			b->add_line(ln);
		}
		ret->add_bookmark(b);
	}
	return ret;
}
