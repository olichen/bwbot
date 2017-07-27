#pragma once
#include "unitstatblock.h"
#include "actionname.h"

struct ActiveUnit {
	UnitStatBlock unit;
	ActionName action;
	int timer;
};
