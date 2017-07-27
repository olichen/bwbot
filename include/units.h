#pragma once
#include "unitname.h"
#include "unitstatblock.h"
#include "exceptions.h"
#include <string>
using namespace std;

class Units
{
	public:
		Units();
		~Units();

		int getId(string unit) const;

		UnitStatBlock getUnitFromId(int unitId) const;
		UnitStatBlock getRaceWorker(char race = 't') const;
		UnitStatBlock getRaceExpansion(char race = 't') const;
		UnitStatBlock getRaceGas(char race = 't') const;

		UnitStatBlock getUnitForRace(char race, bool (UnitStatBlock::*f)()) const;

	private:

		const UnitStatBlock unitStatsList[UnitName::UNIT_TOTAL];
};
