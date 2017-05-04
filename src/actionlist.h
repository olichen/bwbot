// currentaction.h
#pragma once
#include "action.h"
#include <string>
#include <vector>
using namespace std;

class ActionList
{
	public:
		ActionList();

		void updateAction(string action, int timer);

		Action findAction(string action);

	private:
		vector<Action> vActionList;
};
