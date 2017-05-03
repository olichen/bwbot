#pragma once
#include <string>
using namespace std;

class Unit
{
	public:
		Unit(string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided, string prereq, string buildsFrom);

		void init(Unit &prereq, Unit &buildsFrom);
		void update();

		int getMineralCost() { return mMineralCost; }
		int getGasCost() { return mGasCost; }
		int getSupplyCost() { return mSupplyCost; }
		int getSupplyProvided() { return mSupplyProvided; }
		int getBuildTime() { return mBuildTime; }
		string getName() { return mName; }
		string findPrereq() { return mPrereq; }
		string findBuildsFrom() { return mBuildsFrom; }
		Unit* getPrereq() { return pPrereq; }
		Unit* getBuildsFrom() { return pBuildsFrom; }

	private:
		int mMineralCost, mGasCost, mSupplyCost, mSupplyProvided, mBuildTime;
		string mName, mPrereq, mBuildsFrom;
		Unit* pPrereq;
		Unit* pBuildsFrom;
};
