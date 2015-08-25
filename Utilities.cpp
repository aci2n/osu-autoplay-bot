#include "stdafx.h"
#include "Utilities.h"

Utilities::Utilities()
{
}


Utilities::~Utilities()
{
}

std::vector<std::string> Utilities::split(std::string base, std::string delim)
{
	std::string token;
	int pos;
	std::vector<std::string> tokens;
	while ((pos = base.find(delim)) != std::string::npos) {
		token = base.substr(0, pos);
		base = base.substr(pos + 1, base.length());
		tokens.push_back(token);
	}
	if (base.length() > 0)
	{
		tokens.push_back(base);
	}
	return tokens;
}

bool Utilities::contains(std::vector<std::string> v, std::string s)
{
	for (std::string x : v)
	{
		if (x == s)
		{
			return true;
		}
	}
	return false;
}