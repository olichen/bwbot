#pragma once
#include "exceptions.h"
#include <vector>
using namespace std;

class LarvaHandler {
	public:
		void buildHatch();
		void spawnHatch();
		void useLarva();
		int updateLarva();
		void clear();

	private:
		vector<short int> larvaCount;
		vector<short int> timer;
		const short int LARVA_SPAWN_TIME = 342;
};
