#include "action.h"

Action::Action(string nextAction, int nextTimer, string idleAction, int idleTimer)
	: mAction("IDLE"), mTimer(-1), mNextAction(nextAction), mNextTimer(nextTimer), mIdleAction(idleAction), mIdleTimer(idleTimer)
{
	//
}

string Action::update()
{
	switch(mTimer){
		case(-1):
			return NULL;
		case(0):
			mAction = mNextAction;
			mTimer = mNextTimer;
			mNextAction = mIdleAction;
			mNextTimer = mIdleTimer;
			return mAction;
		default:
			mTimer--;
			return NULL;
	}
}
