#ifndef CHUNKS_H
#define CHUNKS_H

#include <memory>
#include <string>
#include <vector>
#include "tools.h"

class chunk
{
	std::string					m_name;
	std::string					m_lcase_name;
	std::vector<std::string>	m_lines;
	std::vector<std::string>	m_tags;
public:
	chunk(const std::string& name);

	void add_line(const std::string& line)
	{
		m_lines.emplace_back(line);
	}

	void add_tag(const std::string& tag)
	{
		m_tags.emplace_back(lcase(tag));
	}

	bool operator==(const std::string& text) const;

	const std::vector<std::string>& get_lines() const { return m_lines; }
	const std::string get_name() const { return m_name; }
};

class chunks
{
	std::string m_name;
	std::vector<std::shared_ptr<chunk>> m_bookmarks;
public:
	chunks(const std::string& name) : m_name(name) {}

	const std::string& get_name() const { return m_name; }
	void add_bookmark(std::shared_ptr<chunk> bookmark) { m_bookmarks.emplace_back(bookmark); }
	std::vector<std::shared_ptr<chunk>> find_bookmarks(const std::string& text) const;
};

#endif // CHUNKS_H
