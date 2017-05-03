#include "currentunit.h"

CurrentUnit::CurrentUnit(Unit &unit, string nextAction, int nextTimer, string idleAction, int idleTimer)
	: pUnit(&unit), mAction(nextAction, nextTimer, idleAction, idleTimer) 
{
	//
}

string CurrentUnit::update()
{
	return mAction.update();
}

