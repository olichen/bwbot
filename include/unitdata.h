#pragma once
#include "unitname.h"
#include "unitstatblock.h"
#include "exceptions.h"
#include <string>
using namespace std;

class UnitData
{
	public:
		UnitData();
		~UnitData();

		int getUnitIdFromName(string name) const;
		UnitStatBlock getUnitFromId(int unitId) const;
		UnitStatBlock getRaceWorker(char race = 't') const;
		UnitStatBlock getRaceExpansion(char race = 't') const;
		UnitStatBlock getRaceGas(char race = 't') const;

	private:
		UnitStatBlock getUnitForRace(char race, bool (UnitStatBlock::*f)()) const;

		const UnitStatBlock unitStatsList[UnitName::UNIT_TOTAL];
};
