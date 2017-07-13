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

		string getActionName() const { return mCurrentAction.getActionName(); }
		string getIdleActionName() const { return mIdleAction.getActionName(); }
		int getTimer() const { return mTimer; }
		string getName() const { return pUnit->getName(); }
		bool isIdle() const { return mTimer == -1; }
		bool hasAddon() const { return mHasAddon; }
		int getCount() const { return mCount; }

		void addAddon() { mHasAddon = true; }
		void setIdleActionTimer(int timer) { mIdleAction.setTimer(timer); }
		void setIdleAction(Action action) { mIdleAction = action; }
		void addCount(int i = 1) { mCount += i; }

	private:
		void nextAction();

		Unit *pUnit;
		Action mCurrentAction;
		queue<Action> vNextAction;
		Action mIdleAction;
		int mTimer, mCount;
		bool mHasAddon;
};
