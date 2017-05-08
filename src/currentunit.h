// currentunit.h
#pragma once
#include "action.h"
#include "unit.h"
#include <string>
#include <queue>
#include <vector>
using namespace std;

class CurrentUnit
{
	public:
		CurrentUnit(Unit &unit, Action nextAction = Action(), Action idleAction = Action());

		void update(vector<Action> &actionList);
		void addNextAction(Action nextAction);
		void gotoAction(Action nextAction);

		string getActionName() { return mCurrentAction.getActionName(); }
		string getIdleActionName() { return mIdleAction.getActionName(); }
		int getTimer() { return mTimer; }
		string getName() { return pUnit->getName(); }
		bool isIdle() { return mTimer == -1; }

		void setIdleActionTimer(int timer) { mIdleAction.setTimer(timer); }
		void setIdleAction(Action action) { mIdleAction = action; }

	private:
		void nextAction();

		Unit *pUnit;
		Action mCurrentAction;
		queue<Action> vNextAction;
		Action mIdleAction;
		int mTimer;
};
