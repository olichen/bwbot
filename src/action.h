// action.h
#pragma once
#include <string>
using namespace std;

class Action
{
	public:
		Action(string action, int timer);

		string getAction() { return mAction; }
		int getTimer() { return mTimer; }
		void setTimer(int timer) { mTimer = timer; }

	private:
		string mAction;
		int mTimer;
};
