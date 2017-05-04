// action.h
#pragma once
#include <string>
using namespace std;

class Action
{
	public:
		Action(string actionName, int timer);

		void setTimer(int timer) { mTimer = timer; }

		string getActionName() { return mActionName; }
		int getTimer() { return mTimer; }

	private:
		string mActionName;
		int mTimer;
};
