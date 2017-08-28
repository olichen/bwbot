#include "activeunit.h"

ActiveUnit::ActiveUnit(int unit, int action, int timer, int count)
	: unit((UnitName)unit), action((ActionName)action), timer(timer), count(count)
{
	//
}

bool ActiveUnit::isAvailable() {
	if (action == ActionName::Idle || action == ActionName::Gather_Minerals)
		return true;
	return false;
}
