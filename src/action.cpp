#include "action.h"

Action::Action()
	: mActionName("IDLE"), mTimer(-1)
{
	//
}

Action::Action(string actionName, int timer)
	: mActionName(actionName), mTimer(timer)
{
	//
}

Action::Action(string actionName, Unit &unit)
	: mActionName(actionName), pTargetUnit(&unit)
{
	//
}

Unit &Action::getTargetUnit()
{
	return *pTargetUnit;
}
