// currentunit.h
#pragma once
#include "action.h"
#include "unit.h"
#include <string>
#include <queue>
using namespace std;

class CurrentUnit
{
	public:
		CurrentUnit(Unit &unit, Action nextAction, Action idleAction);

		string update();
		void addNextAction(Action nextAction);
		void gotoAction(Action nextAction);

		bool isIdle() { return mTimer == -1; }

	private:
		void nextAction();

		Unit *pUnit;
		string mCurrentAction;
		int mTimer;
		queue<Action> vNextAction;
		Action cIdleAction;
};
