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

		UnitName getUnitIdFromName(string) const;
		UnitStatBlock getUnitFromId(UnitName) const;
		UnitStatBlock getRaceWorker(char) const;
		UnitStatBlock getRaceExpansion(char) const;
		UnitStatBlock getRaceGas(char) const;

	private:
		UnitStatBlock getUnitForRace(char race, bool (UnitStatBlock::*)()) const;

		const UnitStatBlock unitStatsList[UnitName::UNIT_TOTAL];
};
