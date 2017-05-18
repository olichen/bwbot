#include "buildorder.hpp"

BuildOrder::BuildOrder()
	: mRace('t')
{
	//
}

void BuildOrder::printBuildOrder() const
{
	for (string buildorder : vBuildOrder)
		cout << buildorder << ", ";
	cout << "\n";
}

void BuildOrder::setLength()
{
	for (unsigned int i = mi; i < vBuildOrder.size(); i++)
		vBuildOrder.pop_back();
}

void BuildOrder::push_back(string build)
{
	if (string_alg::is_empty(build))
		return;

	//check if prefaced with a digit
	int digitcount = 0;
	for ( ; isdigit(build[digitcount]); digitcount++);

	if (digitcount != 0)
		for (int i=0; i < stoi(build.substr(0,digitcount)); i++)
			vBuildOrder.push_back(string_alg::cleanup_input(mRace,build.substr(digitcount)));
	else
		vBuildOrder.push_back(string_alg::cleanup_input(mRace,build));
}
