#pragma once
#include <string>
using namespace std;

class Action
{
	public:
		Action(string nextAction = "IDLE", int nextTimer = -1, string idleAction = "IDLE", int idleTimer = -1);
		string update();

		string getAction() { return mAction; }
		int getTimer() { return mTimer; }

	private:
		int mTimer, mNextTimer, mIdleTimer;
		string mAction, mNextAction, mIdleAction;
};
