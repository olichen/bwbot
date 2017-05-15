#include "build.h"
#include "string_alg.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main( int argc, char *argv[] )
{
	string input = "";
	char race = 't';
	vector<string> buildOrder;
	while (true)
	{
		cout << "Enter a unit name, or hit 'm' for menu': ";
		getline(cin, input);

		//trim input
		input = string_alg::trim(input);
		input = string_alg::to_lower(input);

		if (input == "m")
		{
			cout << " - [R]ace select\n - [D]elete last entry\n - [C]lear build order\n - [L]oad file\n - [Q]uit program\n";
			continue;
		}
		//quit program
		else if (input == "q")
			break;
		//change race
		else if (input == "r")
		{
			cout << "Enter race name ([T]erran, [P]rotoss, [Z]erg): ";
			getline(cin, input);
			char raceChar = tolower(input.at(0));
			if (raceChar == 't' || raceChar == 'p' || raceChar == 'z')
			{
				race = raceChar;
				cout << "Race set\n";
			}
			else
				cout << "Invalid race\n";
			continue;
		}
		//load file
		else if (input == "l")
		{
			cout << "Enter file name (must be in 'buildorders/' directory): ";
			getline(cin, input);
			ifstream buildOrderFile("buildorders/" + input);
			if(buildOrderFile.is_open())
			{
				cout << "Loading build order '" + input + "'\n";
				buildOrder.clear();
				string line = "";
				getline(buildOrderFile, line);
				race = tolower(line.at(0));
				while (getline(buildOrderFile, line))
					buildOrder.push_back(string_alg::cleanup_input(race,line));
				buildOrderFile.close();
			}
			else
			{
				cout << "Unable to open file 'buildorders/" + input + "'\n";
				continue;
			}
		}
		//clear build order
		else if (input == "c")
			buildOrder.clear();
		//delete last entry
		else if (input == "d")
		{
			if (!buildOrder.empty())
				buildOrder.pop_back();
		}
		//add unit
		else
		{
			buildOrder.push_back(string_alg::cleanup_input(race,input));
		}

		try
		{
			Build build;
			build.init(race);
			build.loadBuildOrder(buildOrder);
			build.run();
		}
		catch (const string &ex)
		{
			cout << "Error: " << ex << "\n";
			buildOrder.pop_back();
		}

	}

}
