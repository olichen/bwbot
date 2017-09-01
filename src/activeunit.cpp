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

void ActiveUnit::setActionTravelling(int time) {
	action = ActionName::Travelling;
	timer = time;
}

void ActiveUnit::setActionBuild(int time) {
	action = ActionName::Build;
	timer = time;
}

void ActiveUnit::setActionIdle() {
	action = ActionName::Idle;
	timer = -1;
}

void ActiveUnit::setActionGatherMinerals(int time) {
	action = ActionName::Gather_Minerals;
	timer = time;
}

void ActiveUnit::setActionGatherGas(int time) {
	action = ActionName::Gather_Gas;
	timer = time;
}
