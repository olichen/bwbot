#pragma once
#include "exceptions.h"
#include <vector>
using namespace std;

class LarvaHandler {
	public:
		void addHatch(bool isSpawning = false);
		void useLarva();
		int updateLarva();
		void clear();

	private:
		vector<short int> larvaCount;
		vector<short int> timer;
		const short int LARVA_SPAWN_TIME = 342;
};
