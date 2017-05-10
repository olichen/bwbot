#include "build.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{
	string input = "";
	vector<string> buildOrder;
	while (input != "QUIT" && input != "LOAD")
	{
		cout << "Enter something (LOAD file, DELETE last entry, QUIT program): ";
		getline(cin, input);
		buildOrder.push_back(input);

		if (input == "l" || input == "L" || input == "load")
			input = "LOAD";
		if (input == "q" || input == "Q" || input == "quit")
			input = "QUIT";
		if (input == "d" || input == "D" || input == "delete")
			input = "DELETE";
		if (input == "LOAD" || input == "QUIT")
			continue;
		if (input == "DELETE")
		{
			buildOrder.pop_back();
			if (!buildOrder.empty())
				buildOrder.pop_back();
		}

		Build build;
		build.init();
		build.loadBuildOrder(buildOrder);
		try
		{
			build.run();
		}
		catch (const string &ex)
		{
			cout << "EXCEPTION CAUGHT; PROGRAM TERMINATED\n";
			cout << "" << ex << "\n";
			buildOrder.pop_back();
		}

	}
	if (input == "LOAD")
	{}

}
