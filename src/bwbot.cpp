#include "bwbot.h"

int main() {
	BWBOT bwbot;
	bwbot.init('z');
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

	if(currentUnit.action == ActionName::Next_Frame) {
		// if the unit is a unit and not an action
		if(buildOrder.getUnit()<UnitName::UNIT_TOTAL) {
			if(tryToBuild(buildOrder.getUnit()))
					buildOrder.nextUnit();
		}
		else {}
			// need to handle scout, on gas, off gas, expand
	}
	else {
		addFrameToOutput(currentFrame);
	}
}

void BWBOT::addFrameToOutput(Frame frame) {
		frame.miners = buildHandler.getMineralMinerCount();
		frame.gasminers = buildHandler.getGasMinerCount();
		output.push_back(frame);
}

void BWBOT::testinit() {
	buildOrder.push_back(UnitName::Zerg_Drone);
	buildOrder.push_back(UnitName::Zerg_Drone);
	buildOrder.push_back(UnitName::Zerg_Drone);
	buildOrder.push_back(UnitName::Zerg_Drone);
	buildOrder.push_back(UnitName::Zerg_Drone);
	buildOrder.push_back(UnitName::Zerg_Overlord);
	buildOrder.push_back(UnitName::Zerg_Drone);
	buildOrder.push_back(UnitName::Zerg_Drone);
	buildOrder.push_back(UnitName::Zerg_Drone);
	//buildOrder.push_back(UnitName::Terran_SCV);
	//buildOrder.push_back(UnitName::Terran_SCV);
	//buildOrder.push_back(UnitName::Terran_SCV);
	//buildOrder.push_back(UnitName::Terran_SCV);
	//buildOrder.push_back(UnitName::Terran_SCV);
	//buildOrder.push_back(UnitName::Terran_SCV);
	//buildOrder.push_back(UnitName::Terran_Supply_Depot);
	//buildOrder.push_back(UnitName::Terran_Barracks);
	//buildOrder.push_back(UnitName::Terran_Refinery);
	//buildOrder.push_back(UnitName::Terran_SCV);
	//buildOrder.push_back(UnitName::Terran_SCV);
	//buildOrder.push_back(UnitName::Terran_SCV);
	//buildOrder.push_back(UnitName::Terran_SCV);
	//buildOrder.push_back(UnitName::Terran_Factory);
	//buildOrder.push_back(UnitName::Terran_SCV);
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
		string action = "NULL ";
		if(f.action==ActionName::Idle)
			action = "IDLE ";
		if(f.action==ActionName::Gather_Minerals)
			action = "GATHM";
		if(f.action==ActionName::Gather_Gas)
			action = "GATHG";
		if(f.action==ActionName::Build)
			action = "BUILD";
		if(f.action==ActionName::Being_Built)
			action = "BEING";
		if(f.action==ActionName::Scout)
			action = "SCOUT";
		if(f.action==ActionName::On_Gas)
			action = "ONGAS";
		if(f.action==ActionName::Off_Gas)
			action = "OFGAS";
		if(f.action==ActionName::Expand)
			action = "EXPND";
		if(f.action==ActionName::Extractor_Trick)
			action = "TRICK";
		if(f.action==ActionName::Travelling)
			action = "TRAVL";
		if(f.action==ActionName::Spawning)
			action = "SPAWN";
		if(f.action==ActionName::Start_Build)
			action = "START";
		printf("%s %s\n", action.c_str(), uname.c_str());
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
	if(resourceHandler.canBuild(unitname) && buildHandler.canBuild(unitname)) {
		buildHandler.build(unitname);
		addFrameToOutput(resourceHandler.startBuild(unitname));
		return true;
	}
	return false;
}

void BWBOT::clear() {
	buildHandler.clear();
	buildOrder.clear();
	resourceHandler.clear();
	output.clear();
}
