#include "object.h"

Object::Object(int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided, std::string name, std::string prereq, std::string buildsFrom)
	: mMineralCost(mineralCost), mGasCost(gasCost), mBuildTime(buildTime), mName(name), mSupplyCost(supplyCost), mSupplyProvided(supplyProvided), mPrereq(prereq), mBuildsFrom(buildsFrom)
{
	//
}

void Object::init(Object &prereq, Object &buildsFrom)
{
	pPrereq = &prereq;
	pBuildsFrom = &buildsFrom;
}
