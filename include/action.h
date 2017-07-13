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
		Action(string actionName, int timer, Unit &unit);

		void setTimer(int timer) { mTimer = timer; }

		string getActionName() const { return mActionName; }
		int getTimer() const { return mTimer; }
		bool hasTargetUnit() const { return pTargetUnit != NULL; }
		Unit &getTargetUnit(); 

	private:
		string mActionName;
		int mTimer;
		Unit *pTargetUnit;
};
