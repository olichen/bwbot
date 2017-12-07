#pragma once
#include "frame2.h"
#include "unitdata.h"
#include "activeunit.h"

class ResourceHandler {
	public:
		Frame update(ActiveUnit);
		Frame clear();

	private:
		Frame currentFrame;
		UnitData unitData;
};
