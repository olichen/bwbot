#pragma once
#include "string_alg.hpp"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class BuildOrder
{
	public:
		BuildOrder();

		string getNext() { return (mi < vBuildOrder.size() ? vBuildOrder[mi] : ""); }
		void next() { mi++; }
		bool atEnd() { return mi == vBuildOrder.size(); }

		void reset() { mi = 0; }
		void clear() { mi = 0; vBuildOrder.clear(); }
		void setLength();
		void setRace(char race) { mRace = race; }
		void addToBuildOrder(string build) { vBuildOrder.push_back(string_alg::cleanup_input(mRace,build)); }

		void printBuildOrder() const;
		
	private:
		vector<string> vBuildOrder;
		char mRace;
		unsigned int mi;
};
