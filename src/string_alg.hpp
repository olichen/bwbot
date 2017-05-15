#pragma once
#include <string>
using namespace std;

namespace string_alg
{
	string trim(string s1);
	string titleize(string s1);
	bool lower_eq(string s1, string s2);
	string add_race(char race, string s1);
	string to_lower(string s1);
	string cleanup_input(char race, string s1);
}
