#pragma once
#include <string>
using namespace std;

class Unit
{
	public:
		Unit(int id, string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided,
				string prereq, string buildsFrom, string prereq2 = "", bool isAddon = false, bool reqAddon = false, bool morph = false);

		int getId() const { return mId; }
		int getMineralCost() const { return mMineralCost; }
		int getGasCost() const { return mGasCost; }
		int getSupplyCost() const { return mSupplyCost; }
		int getSupplyProvided() const { return mSupplyProvided; }
		int getBuildTime() const { return mBuildTime; }
		string getName() const { return mName; }
		string getPrereqName() const { return mPrereq; }
		string getPrereq2Name() const { return mPrereq2; }
		bool hasPrereq2() const { return !(mPrereq2==""); }
		string getBuildsFromName() const { return mBuildsFrom; }
		bool isAddon() const { return mIsAddon; }
		bool reqAddon() const { return mReqAddon; }
		bool isMorph() const { return mMorph; }

		bool operator==(const Unit &unit) const { return mName==unit.getName(); }


	private:
		int mId;
		string mName;
		int mMineralCost, mGasCost, mBuildTime, mSupplyCost, mSupplyProvided;
		string mPrereq, mBuildsFrom, mPrereq2;
		bool mIsAddon, mReqAddon, mMorph;
};
