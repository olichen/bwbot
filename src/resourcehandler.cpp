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
		case (Start_Build):
			// use supply money
			break;
		case (Expand):
			// give supply, add mineral patches
			break;
		case (Being_Built):
			// give supply
			break;
		case (Extractor_Trick):
			// use minerals
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
