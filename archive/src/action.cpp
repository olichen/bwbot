#include "action.h"

Action::Action()
	: mActionName("IDLE"), mTimer(-1), pTargetUnit(NULL)
{
	//
}

Action::Action(string actionName, int timer)
	: mActionName(actionName), mTimer(timer), pTargetUnit(NULL)
{
	//
}

Action::Action(string actionName, Unit &unit)
	: mActionName(actionName), mTimer(unit.getBuildTime()), pTargetUnit(&unit)
{
	//
}

Action::Action(string actionName, int timer, Unit &unit)
	: mActionName(actionName), mTimer(timer), pTargetUnit(&unit)
{
	//
}

Unit &Action::getTargetUnit()
{
	return *pTargetUnit;
}
