#include "resourcehandler.h"

Frame ResourceHandler::update(ActiveUnit activeunit) {
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
			// use supply
			break;
		default:
			break;
	//Idle, return nil
	//Build,
	//Start_Build, // use supply
	//Scout, //5 return frame
	//On_Gas, return frame
	//Off_Gas, return frame
	//Expand, return nil
	//Extractor_Trick, add supply
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
