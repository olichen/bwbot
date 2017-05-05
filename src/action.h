// action.h
#pragma once
#include "unit.h"
#include <string>
using namespace std;

class Action
{
	public:
		Action();
		Action(string actionName, int timer = -1);
		Action(string actionName, Unit &unit);

		void setTimer(int timer) { mTimer = timer; }

		string getActionName() { return mActionName; }
		int getTimer() { return mTimer; }
		Unit &getTargetUnit(); 

	private:
		string mActionName;
		int mTimer;
		Unit *pTargetUnit;
};
