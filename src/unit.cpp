// unit.cpp
#include "unit.h"

Unit::Unit(std::string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided, std::string prereq, std::string buildsFrom)
	: mName(name), mMineralCost(mineralCost), mGasCost(gasCost), mBuildTime(buildTime), mSupplyCost(supplyCost), mSupplyProvided(supplyProvided), mPrereq(prereq), mBuildsFrom(buildsFrom)
{
	//
}

void Unit::init(Unit &prereq, Unit &buildsFrom)
{
	pPrereq = &prereq;
	pBuildsFrom = &buildsFrom;
}
