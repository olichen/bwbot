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
	Next_Frame, //10
	ACTION_TOTAL
};
