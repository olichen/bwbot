// currentunit.cpp
#include "currentunit.h"

CurrentUnit::CurrentUnit(Unit &unit, Action nextAction, Action idleAction)
	: pUnit(&unit), cIdleAction(idleAction)
{
	vNextAction.push_back(nextAction);
}

string CurrentUnit::update()
{
	//
}

