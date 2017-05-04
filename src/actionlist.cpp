// currentaction.cpp
#include "actionlist.h"

ActionList::ActionList()
{
	//
}

void ActionList::init()
{
	addAction("IDLE", -1);
	addAction("MINE MINERALS", 176);
}

void ActionList::addAction(string actionName, int timer)
{
	vActionList.push_back(Action(actionName, timer));
}

void ActionList::updateAction(string actionName, int timer)
{
	for (Action &iAction : vActionList)
	{
		if(iAction.getActionName() == actionName)
		{
			iAction.setTimer(timer);
		}
	}
}

Action &ActionList::findAction(string actionName)
{
	for (Action &iAction : vActionList)
	{
		if (iAction.getActionName() == actionName)
		{
			return iAction;
		}
	}
}
