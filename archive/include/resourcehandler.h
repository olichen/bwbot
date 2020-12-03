#pragma once
#include "frame2.h"
#include "unitdata.h"
#include "activeunit.h"

class ResourceHandler {
	public:
		ResourceHandler();
		bool canBuild(UnitName);
		Frame update(ActiveUnit);
		Frame startBuild(UnitName);
		Frame clear();

	private:
		Frame currentFrame;
		UnitData unitData;
};
