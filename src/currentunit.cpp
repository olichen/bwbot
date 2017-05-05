// currentunit.cpp
#include "currentunit.h"

CurrentUnit::CurrentUnit(Unit &unit, Action nextAction, Action idleAction)
	: pUnit(&unit), mCurrentAction(Action()), mIdleAction(idleAction), mTimer(-1)
{
	vNextAction.push(nextAction);
}

void CurrentUnit::update(vector<Action> &actionList)
{
	switch(mTimer){
		//if currently idle
		case(-1):
			nextAction();
			break;
		//if action completes
		case(1):
			actionList.push_back(mCurrentAction);
			nextAction();
			break;
		//if no action completes, decrement timer
		default:
			mTimer--;
			break;
	}
}

void CurrentUnit::addNextAction(Action nextAction)
{
	vNextAction.push(nextAction);
}

//clear all actions and goto a specific one
void CurrentUnit::gotoAction(Action nextAction)
{
	mCurrentAction = nextAction;
	mTimer = nextAction.getTimer();
	vNextAction = queue<Action>();
}

void CurrentUnit::nextAction()
{
	if (vNextAction.empty())
	{
		mCurrentAction = mIdleAction;
		mTimer = mIdleAction.getTimer();
	}
	else
	{
		mCurrentAction = vNextAction.front();
		mTimer = vNextAction.front().getTimer();
		vNextAction.pop();
	}
}
