#include "resourcehandler.h"

Frame ResourceHandler::update(ActiveUnit activeunit) {
	switch(activeunit.action) {
		case (Next_Frame):
			currentFrame.frame++;
			break;
		case (Gather_Minerals):
			currentFrame.minerals++;
			break;
		case (Gather_Gas):
			currentFrame.gas++;
		case (Spawning):
			// use supply
			break;
		default:
			break;
	//Idle,
	//Gather_Minerals,
	//Gather_Gas,
	//Build,
	//Being_Built,
	//Scout, //5
	//On_Gas,
	//Off_Gas,
	//Expand,
	//Extractor_Trick,
	//Travelling, //10
	//Spawning,
	//Next_Frame,
	//ACTION_TOTAL,
	//ACTION_NULL
	}
	return currentFrame;
}

Frame ResourceHandler::clear() {
	Frame newFrame = { 0, 50, 0, 0, 0, 0, 0, UnitName::UNIT_NULL, ActionName::ACTION_NULL };
	currentFrame = newFrame;
	return currentFrame;
}
