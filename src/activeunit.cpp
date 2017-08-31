#include "activeunit.h"

ActiveUnit::ActiveUnit(int unit, int action, int timer)
	: unit((UnitName)unit), action((ActionName)action), timer(timer)
{
	//
}

bool ActiveUnit::isAvailable() {
	if (action == ActionName::Idle || action == ActionName::Gather_Minerals)
		return true;
	return false;
}

void ActiveUnit::setTravelling(int time) {
	action = ActionName::Travelling;
	timer = time;
}
