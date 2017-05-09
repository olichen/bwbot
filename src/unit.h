// unit.h
#pragma once
#include <string>
using namespace std;

class Unit
{
	public:
		Unit(string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided,
				string prereq, string buildsFrom, bool isAddon = false, bool reqAddon = false);

		void init(Unit &prereq, Unit &buildsFrom);

		int getMineralCost() const { return mMineralCost; }
		int getGasCost() const { return mGasCost; }
		int getSupplyCost() const { return mSupplyCost; }
		int getSupplyProvided() const { return mSupplyProvided; }
		int getBuildTime() const { return mBuildTime; }
		string getName() const { return mName; }
		string getPrereqName() const { return mPrereq; }
		string getBuildsFromName() const { return mBuildsFrom; }
		bool isAddon() const { return mIsAddon; }
		bool reqAddon() const { return mReqAddon; }

		bool operator==(const Unit &unit) const { return mName==unit.getName(); }

	private:
		string mName;
		int mMineralCost, mGasCost, mBuildTime, mSupplyCost, mSupplyProvided;
		string mPrereq, mBuildsFrom;
		bool mIsAddon, mReqAddon;
};
