#include "chunks.h"
#include "tools.h"

chunk::chunk(const std::string &name) : m_name(name)
{
	m_lcase_name = lcase(name);
}

bool chunk::operator==(const std::string &text) const
{
	if(m_lcase_name.find(text) != std::string::npos) return true;
	auto tokens = split_string(text, " ");
	bool found;
	for(const auto& tok : tokens)
	{
		found = false;
		for(const auto& tag : m_tags)
		{
			if(!tok.empty())
			{
				if(tag == tok)
				{
					found = true;
					break;
				}
			}
		}
		if(!found) return false;
	}
	return true;
}

std::vector<std::shared_ptr<chunk>> chunks::find_bookmarks(const std::string &text) const
{
	if(text.empty()) return m_bookmarks;
	std::vector<std::shared_ptr<chunk>> ret;
	for(const auto& bookmark : m_bookmarks)
	{
		if(*bookmark == text) ret.push_back(bookmark);
	}
	return ret;
}
