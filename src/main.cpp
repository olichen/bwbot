#include "build.h"
#include "string_alg.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	string input = "";
	char race = 't';
	vector<string> buildOrder;
	while (true)
	{
		cout << "Enter something ([l]oad file, [c]lear build order, [d]elete last entry, select [r]ace, [q]uit program, unit name): ";
		getline(cin, input);

		//trim input
		input = string_alg::trim(input);

		//quit program
		if (input == "q")
			break;
		//change race
		else if (input == "r")
		{
			cout << "Enter race name (Terran, Protoss, Zerg): ";
			getline(cin, input);
			race = tolower(input.at(0));
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
				while (getline(buildOrderFile, line))
				{
					cout << line;
					buildOrder.push_back(string_alg::titleize(input));
				}
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
		else
		{
			input = string_alg::add_race(race, input);
			buildOrder.push_back(string_alg::titleize(input));
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
