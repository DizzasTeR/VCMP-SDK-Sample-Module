#pragma once
#include "../pch.h"

void raw_split(const std::string& s, char delim, std::vector<std::string>& elems)
{
	std::stringstream ss(s);
	std::string item;
	while(getline(ss, item, delim)) {
		if(!item.empty())
			elems.push_back(item);
	}
}

namespace std {

	std::vector<std::string> split(const std::string& s, char delim)
	{
		std::vector<std::string> elems;
		raw_split(s, delim, elems);
		return elems;
	}

}