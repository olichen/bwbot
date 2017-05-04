// currentunit.h
#pragma once
#include "action.h"
#include "unit.h"
#include <string>
#include <vector>
using namespace std;

class CurrentUnit
{
	public:
		CurrentUnit(Unit &unit, Action nextAction, Action idleAction);

		string update();

		//bool isIdle() { return mAction.isIdle(); }

	private:
		Unit *pUnit;
		vector<Action> vNextAction;
		Action cIdleAction;
};
