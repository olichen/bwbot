#include "activeunit.h"

ActiveUnit::ActiveUnit(int unit, int action, int timer)
	: unit((UnitName)unit), action((ActionName)action), timer(timer)
{
	//
}

bool ActiveUnit::isIdle() {
	if (action == ActionName::Idle || action == ActionName::Gather_Minerals)
		return true;
	return false;
}
