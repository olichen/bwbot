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
