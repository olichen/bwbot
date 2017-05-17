// resources.cpp
#include "resources.h"

Resources::Resources(int mineralPatches, int gasGeysers, char race)
	: mMinerals(0), mGas(0), mSupply(0), mSupplyMax(0), mFrame(0), mMineralPatches(mineralPatches), mGasGeysers(gasGeysers), mRace(race)
{
	//
}

void Resources::addExpansion(int mineralPatches, int gasGeysers)
{
	mMineralPatches += mineralPatches;
	mGasGeysers += gasGeysers;
}

int Resources::getBaseMineRate() const
{
	if (mRace=='t')
		return 176;
	if (mRace=='z')
		return 172;
	if (mRace=='p')
		return 168;
	throw "Race  not found.";
}
