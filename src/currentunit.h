#pragma once
#include "action.h"
#include "unit.h"
#include <string>
using namespace std;

class CurrentUnit
{
	public:
		CurrentUnit(Unit &unit, string nextAction = "IDLE", int nextTimer = -1, string idleAction = "IDLE", int idleTimer = -1);

		string update();

		bool isIdle() { return mAction.isIdle(); }
		string getAction() { return mAction.getAction(); }
		int getActionTimer() { return mAction.getTimer(); }

	private:
		Unit *pUnit;
		Action mAction;
};
