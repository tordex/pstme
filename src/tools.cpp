#include "tools.h"

std::string lcase(const std::string& s)
{
	std::string ret;
	for(auto i : s)
	{
		ret += (char)std::tolower(i);
	}
	return ret;
}

std::string& trim(std::string& s, const std::string& chars_to_trim)
{
	std::string::size_type pos = s.find_first_not_of(chars_to_trim);
	if(pos != std::string::npos)
	{
		s.erase(s.begin(), s.begin() + pos);
	}
	else
	{
		s = "";
		return s;
	}
	pos = s.find_last_not_of(chars_to_trim);
	if(pos != std::string::npos)
	{
		s.erase(s.begin() + pos + 1, s.end());
	}
	return s;
}

std::vector<std::string> split_string(const std::string& str, const std::string& delims)
{
	if(str.empty() || delims.empty())
	{
		return {};
	}

	std::vector<std::string> tokens;

	std::string all_delims = delims;

	std::string::size_type token_start	= 0;
	std::string::size_type token_end	= str.find_first_of(all_delims, token_start);
	std::string::size_type token_len;
	std::string token;
	while(true)
	{
		if(token_end == std::string::npos)
		{
			token_len = std::string::npos;
		} else
		{
			token_len = token_end - token_start;
		}

		token = str.substr(token_start, token_len);
		if(!token.empty())
		{
			tokens.push_back( token );
		}

		token_start = token_end;
		if(token_start == std::string::npos) break;
		token_start++;
		if(token_start == str.length()) break;
		token_end = str.find_first_of(all_delims, token_start);
	}
	return tokens;
}
