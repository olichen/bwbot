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

		void init();
		void addAction(string actionName, int timer);
		void updateAction(string actionName, int timer);

		Action &findAction(string actionName);

	private:
		vector<Action> vActionList;
};
