#include "resourcehandler.h"

ResourceHandler::ResourceHandler() {
	clear();
}

bool ResourceHandler::canBuild(UnitName unitName) {
	UnitStatBlock unit = unitData.getUnitFromId(unitName);

	if(currentFrame.supplymax - currentFrame.supply >= unit.supplyCost)
		if(currentFrame.minerals >= unit.mineralCost && currentFrame.gas >= unit.gasCost)
			return true;

	return false;
}

Frame ResourceHandler::update(ActiveUnit activeunit) {
	currentFrame.unit = activeunit.unit;
	currentFrame.action = activeunit.action;
	UnitStatBlock unitStats;
	if(activeunit.unit<UnitName::UNIT_NULL)
		unitStats = unitData.getUnitFromId(activeunit.unit);

	switch(activeunit.action) {
		case (Next_Frame):
			currentFrame.frame++;
			break;
		case (Gather_Minerals):
			currentFrame.minerals += 8;
			break;
		case (Gather_Gas):
			currentFrame.gas += 8;
			break;
		case (Spawning):
			currentFrame.supply += unitStats.supplyCost;
			currentFrame.supplymax += unitStats.supplyProvided;
			break;
		case (Start_Build):
				currentFrame.supply += unitStats.supplyCost;
				if(unitStats.isMorph())
					currentFrame.supply -= unitData.getUnitFromId(unitStats.buildsFrom).supplyCost;
				currentFrame.minerals -= unitStats.mineralCost;
				currentFrame.gas -= unitStats.gasCost;
				break;
		case (Expand):
			currentFrame.supplymax += unitStats.supplyProvided;
			break;
		case (Being_Built):
			currentFrame.supplymax += unitStats.supplyProvided;
			break;
		case (Extractor_Trick):
			currentFrame.minerals -= 17;
			break;
		case (On_Gas):
		case (Off_Gas):
		case (Scout):
		case (Idle):
		default:
			break;
	}
	return currentFrame;
}

Frame ResourceHandler::startBuild(UnitName unitname) {
		ActiveUnit startBuildUnit(unitname, ActionName::Start_Build, -1);
		return update(startBuildUnit);
}

Frame ResourceHandler::clear() {
	Frame newFrame = { 0, 50, 0, 0, 0, 0, 0, UnitName::UNIT_NULL, ActionName::ACTION_NULL };
	currentFrame = newFrame;
	return currentFrame;
}
