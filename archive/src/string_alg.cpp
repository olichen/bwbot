#include "string_alg.h"

bool string_alg::is_empty(string s1)
{
	if (s1=="")
		return true;
	if (trim(s1)=="")
		return true;
	return false;
}

string string_alg::trim(string s1)
{
	int first_char = 0;
	int last_char = s1.length();
	for (unsigned int i=0; i<s1.length(); i++)
	{
		if (!isspace(s1[i]))
			last_char = i;
		if (!isspace(s1[s1.length()-i-1]))
			first_char = s1.length()-i-1;
	}
	return s1.substr(first_char, last_char - first_char + 1);
}

string string_alg::titleize(string s1)
{
	char lastChar = ' ';
	for (unsigned int i=0; i<s1.length(); i++)
	{
		if (lastChar == ' ')
			s1[i] = toupper(s1[i]);
		else
			s1[i] = tolower(s1[i]);
		lastChar = s1[i];
	}
	if (s1 == "Terran Scv")
		return "Terran SCV";
	return s1;
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

string string_alg::to_lower(string s1)
{
	for (unsigned int i=0; i<s1.length(); i++)
		s1[i] = tolower(s1[i]);
	return s1;
}

string string_alg::add_race(char race, string s1)
{
	if (lower_eq("search", s1))
		return "SEARCH";
	if (lower_eq("off gas", s1))
		return "OFF GAS";
	if (lower_eq("on gas", s1))
		return "ON GAS";
	if (lower_eq("expand", s1))
		return "EXPAND";
	if (lower_eq("extractor trick", s1))
		return "EXTRACTOR TRICK";
	else if (race == 't')
	{
		if (!lower_eq(s1.substr(0,7), "terran "))
			return titleize("Terran " + s1);
	}
	else if (race == 'z')
	{
		if (!lower_eq(s1.substr(0,5), "zerg "))
			return titleize("Zerg " + s1);
	}
	else if (race == 'p')
	{
		if (!lower_eq(s1.substr(0,8), "protoss "))
			return titleize("Protoss " + s1);
	}
	return s1;
}

string string_alg::cleanup_input(char race, string s1)
{
	return add_race(race, titleize(trim(s1)));
}
