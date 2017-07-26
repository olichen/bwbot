#pragma once
#include "unitname.h"
#include "unitstats.h"
#include "exceptions.h"
#include <string>
using namespace std;

class Units
{
	public:
		Units();
		~Units();

		int getId(string unit) const;

		UnitStats getUnitFromId(int unitId) const;
		UnitStats getRaceWorker(char race = 't') const;
		UnitStats getRaceExpansion(char race = 't') const;
		UnitStats getRaceGas(char race = 't') const;

		UnitStats getUnitForRace(char race, bool (UnitStats::*f)()) const;

	private:

		const UnitStats unitStatsList[UnitName::UNIT_TOTAL];
};
