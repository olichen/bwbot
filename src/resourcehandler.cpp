#include "resourcehandler.h"

bool ResourceHandler::canBuild(UnitName unitName) {
	UnitStatBlock unit = unitData.getUnitFromId(unitName);

	if(currentFrame.supplymax - currentFrame.supply > unit.supplyCost)
		if(currentFrame.minerals > unit.mineralCost)
			if(currentFrame.gas > unit.gasCost)
				return true;

	return false;
}

Frame ResourceHandler::update(ActiveUnit activeunit) {
	currentFrame.unit = activeunit.unit;
	currentFrame.action = activeunit.action;

	switch(activeunit.action) {
		case (Next_Frame):
			currentFrame.frame++;
			break;
		case (Gather_Minerals):
			currentFrame.minerals += 8;
			break;
		case (Gather_Gas):
			currentFrame.gas += 8;
		case (Spawning):
			currentFrame.supply += unitData.getUnitFromId(activeunit.unit).supplyCost;
			currentFrame.supplymax += unitData.getUnitFromId(activeunit.unit).supplyProvided;
			break;
		case (Start_Build):
			currentFrame.supply += unitData.getUnitFromId(activeunit.unit).supplyCost;
			currentFrame.minerals -= unitData.getUnitFromId(activeunit.unit).mineralCost;
			currentFrame.gas -= unitData.getUnitFromId(activeunit.unit).gasCost;
			break;
		case (Expand):
			currentFrame.supplymax += unitData.getUnitFromId(activeunit.unit).supplyProvided;
			break;
		case (Being_Built):
			currentFrame.supplymax += unitData.getUnitFromId(activeunit.unit).supplyProvided;
			break;
		case (Extractor_Trick):
			currentFrame.minerals -= 17;
			break;
		case (On_Gas):
		case (Off_Gas):
		case (Scout):
			// update miners
			break;
		default:
			Frame newFrame;
			newFrame.frame = -1;
			return newFrame;
			break;
	}
	return currentFrame;
}

Frame ResourceHandler::clear() {
	Frame newFrame = { 0, 50, 0, 0, 0, 0, 0, UnitName::UNIT_NULL, ActionName::ACTION_NULL };
	currentFrame = newFrame;
	return currentFrame;
}
