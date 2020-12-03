#include "larvahandler.h"

void LarvaHandler::buildHatch() {
	larvaCount.push_back(1);
	timer.push_back(LARVA_SPAWN_TIME);
	larvaIterator = timer.begin();
}

void LarvaHandler::spawnHatch() {
	larvaCount.push_back(3);
	timer.push_back(LARVA_SPAWN_TIME);
	larvaIterator = timer.begin();
}

void LarvaHandler::useLarva() {
	int hatchWithMostLarva = -1;
	for(unsigned int i=0; i<timer.size(); i++) {
		if(larvaCount[i] > larvaCount[hatchWithMostLarva])
			hatchWithMostLarva = i;
		if(larvaCount[i] == larvaCount[hatchWithMostLarva])
			if(timer[i] > timer[hatchWithMostLarva])
				hatchWithMostLarva = i;
	}
	if(hatchWithMostLarva == -1)
		throw UnitNotFound();
	larvaCount[hatchWithMostLarva] -= 1;
	larvaIterator = timer.begin();
}

bool LarvaHandler::updateLarva() {
	for(;larvaIterator != timer.end();larvaIterator++) {
		short int i = larvaIterator - timer.begin();
		if(timer[i] == 0) {
			larvaCount[i] += 1;
			timer[i] = LARVA_SPAWN_TIME;
			return true;
		}
		else if(larvaCount[i]<3)
			timer[i] -= 1;
	}
	larvaIterator = timer.begin();
	return false;
}

void LarvaHandler::clear() {
	timer.clear();
	larvaCount.clear();
}
