#include "string_alg.hpp"

string string_alg::to_lower(string s1)
{
	return "";
}

string string_alg::titleize(string s1)
{
	return "";
}

bool string_alg::lower_eq(string s1, string s2)
{
	if (s1.length() != s2.length())
		return false;
	for (unsigned int i=0; i<s1.length(); i++)
		if (tolower(s1.at(i)) != tolower(s2.at(i)))
			return false;
	return true;
}
