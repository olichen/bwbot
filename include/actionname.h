#pragma once

enum ActionName : unsigned char {
	Idle,
	Gather_Minerals,
	Gather_Gas,
	Build,
	Being_Built,
	Scout,
	On_Gas,
	Off_Gas,
	Expand,
	Extractor_Trick,
	ACTION_TOTAL,
	ACTION_NULL
};
