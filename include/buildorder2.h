#pragma once
#include "unitname.h"
#include <vector>
#include <iterator>
using namespace std;

class BuildOrder
{
	public:
		BuildOrder();

		UnitName getUnit() { return *buildOrderIterator; }
		void nextUnit() { buildOrderIterator++; }
		bool atEnd() { return buildOrderIterator == buildOrder.end(); }

		void push_back(UnitName unit) { buildOrder.push_back(unit); }
		void pop() { buildOrder.pop_back(); }
		void clear() { buildOrder.clear(); buildOrderIterator = buildOrder.begin(); }

		//void printBuildOrder() const;
		
	private:
		vector<UnitName>::iterator buildOrderIterator;
		vector<UnitName> buildOrder;
};
