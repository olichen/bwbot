#pragma once
#include "resources.h"

class Build
{
	public:
		Build();
		~Build();

		void init();

	private:
		Resources resources;
		void update();
		void printResources();
};
