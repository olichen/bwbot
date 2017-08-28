#include "activeunit.h"

ActiveUnit::ActiveUnit(int unit, int action, int timer, int count, int counttimer)
	: unit((UnitName)unit), action((ActionName)action), timer(timer), count(count), counttimer(counttimer)
{
	//
}

bool ActiveUnit::isAvailable() {
	if (action == ActionName::Idle || action == ActionName::Gather_Minerals)
		return true;
	return false;
}
