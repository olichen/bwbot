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

bool ActiveUnit::isSpawning() {
	if (action == ActionName::Spawning || action == ActionName::Being_Built)
		return true;
	return false;
}
