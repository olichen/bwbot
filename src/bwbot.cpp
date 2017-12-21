#include "bwbot.h"

void BWBOT::init(char race) {
	clear();
	if(race=='t') {
		for(int i=0; i<4; i++)
			buildHandler.spawn(UnitName::Terran_SCV);
		buildHandler.spawn(UnitName::Terran_Command_Center);
	}
	if(race=='p') {
		for(int i=0; i<4; i++)
			buildHandler.spawn(UnitName::Protoss_Probe);
		buildHandler.spawn(UnitName::Protoss_Nexus);
	}
	if(race=='z') {
		for(int i=0; i<4; i++)
			buildHandler.spawn(UnitName::Zerg_Drone);
		buildHandler.spawn(UnitName::Zerg_Hatchery);
		buildHandler.spawn(UnitName::Zerg_Overlord);
	}
}

bool BWBOT::tryToBuild(UnitName unitname) {
	if(resourceHandler.canBuild(unitname)) {
		if(buildHandler.canBuild(unitname)) {
			buildHandler.build(unitname);
			return true;
		}
	}
	return false;
}

void BWBOT::clear() {
	buildHandler.clear();
	buildOrder.clear();
	resourceHandler.clear();
	output.clear();
}
