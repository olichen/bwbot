#pragma once

enum ActionName : unsigned char {
	Idle,
	Gather_Minerals,
	Gather_Gas,
	Build,
	Being_Built,
	Scout, //5
	On_Gas,
	Off_Gas,
	Expand,
	Extractor_Trick,
	Travelling, //10
	Spawning,
	Next_Frame,
	ACTION_TOTAL,
	ACTION_NULL
};
