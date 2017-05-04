// action.cpp
#include "action.h"

Action::Action(string nextAction, int nextTimer, string idleAction, int idleTimer)
	: mAction("IDLE"), mTimer(-1), mNextAction(nextAction), mNextTimer(nextTimer), mIdleAction(idleAction), mIdleTimer(idleTimer)
{
	//
}

string Action::update()
{
	switch(mTimer){
		//if idle
		case(-1):
			return "";
		//if action completes
		case(0):
			mAction = mNextAction;
			mTimer = mNextTimer;
			mNextAction = mIdleAction;
			mNextTimer = mIdleTimer;
			return mAction;
		//if no action completes, decrement timer
		default:
			mTimer--;
			return "";
	}
}
