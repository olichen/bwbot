#include "build.h"
#include <iostream>
#include <string>
using namespace std;

int main( int argc, char *argv[] )
{
	bool interactive = (argc == 2 ? false : true);

	Build build;

	if (!interactive)
	{
		try
		{
			build.loadFile(argv[1]);
			build.run();
		}
		catch (const string &ex)
		{
			cout << "Error: " << ex << "\n";
		}
	}

	while (interactive)
	{
		string input = "";
		cout << "Enter a unit name, or hit 'm' for menu': ";
		getline(cin, input);

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
			try
			{
				build.init(raceChar);
			}
			catch (const string &ex)
			{
				cout << "Error: " << ex << "\n";
			}
			continue;
		}
		////load file
		else if (input == "l")
		{
			cout << "Enter file name (must be in 'buildorders/' directory): ";
			getline(cin, input);
			try
			{
				build.loadFile(input);
			}
			catch (const string &ex)
			{
				cout << "Error: " << ex << "\n";
			}
		}
		//clear build order
		else if (input == "c")
			build.clear();
		//delete last entry
		else if (input == "d")
			build.popBuildOrder();
		//add unit
		else
			build.pushBuildOrder(input);

		build.run();
	}
}
