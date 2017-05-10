#include "build.h"
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
		cout << "Enter something (LOAD file, DELETE last entry, QUIT program, RACE select): ";
		getline(cin, input);
		buildOrder.push_back(input);

		//input aliases
		char inputChar = tolower(input.at(0));

		//quit program
		if (inputChar == 'q')
			break;
		//change race
		if (inputChar == 'r')
		{
			cout << "Enter race name (Terran, Protoss, Zerg): ";
			getline(cin, input);
			race = tolower(input.at(0));
			continue;
		}
		//load file
		if (inputChar == 'l')
		{
			cout << "Enter file name (must be in '/buildorders' directory): ";
			getline(cin, input);
			ofstream buildOrderFile;
			buildOrderFile.open("/buildorders/" + input);
		}
		//delete last entry
		if (inputChar == 'd')
		{
			buildOrder.pop_back();
			if (!buildOrder.empty())
				buildOrder.pop_back();
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
