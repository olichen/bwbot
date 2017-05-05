// unit.h
#pragma once
#include "action.h"
#include <string>
using namespace std;

class Unit
{
	public:
		Unit(string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided, string prereq, string buildsFrom);

		void init(Unit &prereq, Unit &buildsFrom);

		int getMineralCost() { return mMineralCost; }
		int getGasCost() { return mGasCost; }
		int getSupplyCost() { return mSupplyCost; }
		int getSupplyProvided() { return mSupplyProvided; }
		int getBuildTime() { return mBuildTime; }
		string getName() { return mName; }
		string getPrereqName() { return mPrereq; }
		string getBuildsFromName() { return mBuildsFrom; }
		Unit *getPrereq() { return pPrereq; }
		Unit *getBuildsFrom() { return pBuildsFrom; }

	private:
		string mName;
		int mMineralCost, mGasCost, mBuildTime, mSupplyCost, mSupplyProvided;
		string mPrereq, mBuildsFrom;
		Unit *pPrereq;
		Unit *pBuildsFrom;
};
