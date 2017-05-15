// unit.cpp
#include "unit.h"

Unit::Unit(string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided,
		string prereq, string buildsFrom, string prereq2, bool isAddon, bool reqAddon, bool morph)
	: mName(name), mMineralCost(mineralCost), mGasCost(gasCost), mBuildTime(buildTime), mSupplyCost(supplyCost), mSupplyProvided(supplyProvided),
		mPrereq(prereq), mBuildsFrom(buildsFrom), mPrereq2(prereq2), mIsAddon(isAddon), mReqAddon(reqAddon), mMorph(morph)
{
	//
}
