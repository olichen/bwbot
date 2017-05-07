// resources.cpp
#include "resources.h"

Resources::Resources(int mineralPatches, int gasGeysers)
	: mMinerals(0), mGas(0), mSupply(0), mSupplyMax(0), mFrame(0), mMineralPatches(mineralPatches), mGasGeysers(gasGeysers)
{
	//
}

void Resources::addExpansion(int mineralPatches, int gasGeysers)
{
	mMineralPatches += mineralPatches;
	mGasGeysers += gasGeysers;
}
