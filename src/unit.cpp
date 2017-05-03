#include "unit.h"

Unit::Unit(std::string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided, std::string prereq, std::string buildsFrom)
	: mMineralCost(mineralCost), mGasCost(gasCost), mBuildTime(buildTime), mName(name), mSupplyCost(supplyCost), mSupplyProvided(supplyProvided), mPrereq(prereq), mBuildsFrom(buildsFrom)
{
	//
}

void Unit::init(Unit &prereq, Unit &buildsFrom)
{
	pPrereq = &prereq;
	pBuildsFrom = &buildsFrom;
}

string Unit::update()
{
	return mAction.update();
}
