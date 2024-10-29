#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <vector>

extern std::string lcase(const std::string& s);
extern std::string& trim(std::string& s, const std::string& chars_to_trim);
extern std::vector<std::string> split_string(const std::string& str, const std::string& delims);

#endif // TOOLS_H
