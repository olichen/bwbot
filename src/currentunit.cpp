// currentunit.cpp
#include "currentunit.h"

CurrentUnit::CurrentUnit(Unit &unit, Action nextAction, Action idleAction)
	: pUnit(&unit), mCurrentAction("IDLE"), cIdleAction(idleAction), mTimer(-1)
{
	vNextAction.push(nextAction);
}

string CurrentUnit::update()
{
	switch(mTimer){
		//if currently idle
		case(-1):
			nextAction();
			return "";
		//if action completes
		case(1):
			{
				string currentAction = mCurrentAction;
				nextAction();
				return currentAction;
			}
		//if no action completes, decrement timer
		default:
			mTimer--;
			return "";
	}
}

void CurrentUnit::addNextAction(Action nextAction)
{
	vNextAction.push(nextAction);
}

//clear all actions and goto a specific one
void CurrentUnit::gotoAction(Action nextAction)
{
	mCurrentAction = nextAction.getActionName();
	mTimer = nextAction.getTimer();
	vNextAction = queue<Action>();
}

void CurrentUnit::nextAction()
{
	if (vNextAction.empty())
	{
		mCurrentAction = cIdleAction.getActionName();
		mTimer = cIdleAction.getTimer();
	}
	else
	{
		mCurrentAction = vNextAction.front().getActionName();
		mTimer = vNextAction.front().getTimer();
		vNextAction.pop();
	}
}
