#pragma once
#include <string>

class Unit
{
	public:
		Unit();

	private:
		int mMineralCost, mGasCost, mSupplyCost, mBuildTime;
		std::string mName;
};
