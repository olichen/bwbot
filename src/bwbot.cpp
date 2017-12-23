#include "bwbot.h"

int main() {
	BWBOT bwbot;
	bwbot.init('t');
	bwbot.testinit();
	bwbot.run();
	bwbot.testprint();
	return 0;
}

void BWBOT::run() {
	int i=0;
	while(!buildOrder.atEnd()&&i<10000) {
		update();
		i++;
	}
}

void BWBOT::update() {
	ActiveUnit currentUnit = buildHandler.update();
	Frame currentFrame = resourceHandler.update(currentUnit);
	if(currentUnit.action == ActionName::Next_Frame)
		if(tryToBuild(buildOrder.getUnit()))
				buildOrder.nextUnit();
	if(currentUnit.action != ActionName::Next_Frame) {
		currentFrame.miners = buildHandler.getMineralMinerCount();
		currentFrame.gasminers = buildHandler.getGasMinerCount();
		output.push_back(currentFrame);
	}
}

void BWBOT::testinit() {
	buildOrder.push_back(UnitName::Terran_SCV);
	buildOrder.push_back(UnitName::Terran_SCV);
	buildOrder.push_back(UnitName::Terran_SCV);
	buildOrder.push_back(UnitName::Terran_SCV);
	buildOrder.push_back(UnitName::Terran_SCV);
	buildOrder.push_back(UnitName::Terran_Supply_Depot);
	buildOrder.push_back(UnitName::Terran_SCV);
	buildOrder.push_back(UnitName::Terran_SCV);
	buildOrder.push_back(UnitName::Terran_Barracks);
	buildOrder.push_back(UnitName::Terran_SCV);
	//buildOrder.push_back(UnitName::Terran_Refinery);
	//buildOrder.push_back(UnitName::Terran_Command_Center);
}

void BWBOT::testprint() {
	for(int i=0; i<(int)output.size(); i++) {
		Frame f = output[i];
		printf("%6d %3d %3d ", f.frame, f.minerals, f.gas);
		printf("%3d/%3d ", f.supply, f.supplymax);
		printf("%2d %2d ", f.miners, f.gasminers);
		string uname = "NULL";
		if(f.unit != UnitName::UNIT_NULL)
			uname = unitData.getUnitFromId(f.unit).name;
		printf("%2d %s\n", f.action, uname.c_str());
	}
}

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
			ActiveUnit abcarg(unitname, ActionName::Start_Build, 150);
			output.push_back(resourceHandler.update(abcarg));
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
