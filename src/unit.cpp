// unit.cpp
#include "unit.h"

Unit::Unit(string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided,
		string prereq, string buildsFrom, bool isAddon, bool reqAddon)
	: mName(name), mMineralCost(mineralCost), mGasCost(gasCost), mBuildTime(buildTime), mSupplyCost(supplyCost), mSupplyProvided(supplyProvided),
		mPrereq(prereq), mBuildsFrom(buildsFrom), mIsAddon(isAddon), mReqAddon(reqAddon)
{
	//
}
