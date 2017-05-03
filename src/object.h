#pragma once
#include <string>

class Object
{
	public:
		Object(int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided, std::string name, std::string prereq, std::string buildsFrom);

		void init(Object &prereq, Object &buildsFrom);
		void update();

		int getMineralCost() { return mMineralCost; }
		int getGasCost() { return mGasCost; }
		int getSupplyCost() { return mSupplyCost; }
		int getSupplyProvided() { return mSupplyProvided; }
		int getBuildTime() { return mBuildTime; }
		std::string getName() { return mName; }
		Object* getPrereq() { return pPrereq; }
		Object* getBuildsFrom() { return pBuildsFrom; }

	private:
		int mMineralCost, mGasCost, mSupplyCost, mSupplyProvided, mBuildTime;
		std::string mName, mPrereq, mBuildsFrom;
		Object* pPrereq;
		Object* pBuildsFrom;
};
