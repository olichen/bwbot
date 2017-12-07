#pragma once
#include "frame2.h"
#include "unitdata.h"
#include "activeunit.h"

class CurrentFrame {
	public:
		Frame update(ActiveUnit);
		void clear();

	private:
		Frame frame;
		UnitData unitData;
};
