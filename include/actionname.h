#pragma once

enum ActionName : unsigned char {
	Idle, //0
	Gather_Minerals, //1
	Gather_Gas, //2
	Build, //3
	Being_Built, //4
	Scout, //5
	On_Gas, //6
	Off_Gas, //7
	Expand, //8
	Extractor_Trick, //9
	Next_Frame, //10
	ACTION_TOTAL //11
};
