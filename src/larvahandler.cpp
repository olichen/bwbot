#include "larvahandler.h"

void LarvaHandler::addHatch() {
	larvaCount.push_back(1);
	timer.push_back(LARVA_SPAWN_TIME);
}

void LarvaHandler::useLarva() {
	int hatchWithMostLarva = -1;
	for(unsigned int i=0; i<timer.size(); i++) {
		if(hatchWithMostLarva == -1 && larvaCount[i] > 0)
			hatchWithMostLarva = i;
		if(larvaCount[i] > larvaCount[hatchWithMostLarva])
			hatchWithMostLarva = i;
		if(larvaCount[i] == larvaCount[hatchWithMostLarva])
			if(timer[i] > timer[hatchWithMostLarva])
				hatchWithMostLarva = i;
	}
	if(hatchWithMostLarva == -1)
		throw NotEnoughLarva();
	larvaCount[hatchWithMostLarva] -= 1;
}

int LarvaHandler::updateLarva() {
	int spawnLarvaCount = 0;
	for(unsigned int i=0; i<timer.size(); i++) {
		if(timer[i] == 0) {
			larvaCount[i] += 1;
			spawnLarvaCount += 1;
			timer[i] = LARVA_SPAWN_TIME;
		}
		else if(larvaCount[i]<3)
			timer[i] -= 1;
	}
	return spawnLarvaCount;
}
