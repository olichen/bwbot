#include <iostream>
#include "resources.h"

int main()
{
	Resources object;
	std::cout << "HELLO WORLD\n";
	std::cout << object.getMinerals() << "\n";
	object.addMinerals(4);
	std::cout << object.getMinerals() << "\n";
}
