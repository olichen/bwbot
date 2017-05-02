#include "build.h"
#include <iostream>
#include <chrono>

Build::Build()
{
	//
}

Build::~Build()
{
	//
}

void Build::init()
{
	using clock = std::chrono::high_resolution_clock;

	auto time_start = clock::now();
	std::chrono::milliseconds lag(0);
	constexpr std::chrono::milliseconds timestep(10);

	while(true)
	{
		auto time_delta = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<std::chrono::milliseconds>(time_delta);

		while(lag >= timestep)
		{
			lag -= timestep;
			update();
			printResources();
		}
	}
}

void Build::update()
{
	resources.addFrame();
}

void Build::printResources()
{
	printf(" Frame |  Min  |  Gas  | Supply\n");
	printf("%6d |", resources.getFrame());
	printf("%5d  |", resources.getMinerals());
	printf("%5d  |", resources.getGas());
	printf("%4d/%d", resources.getSupply(), resources.getSupplyMax());
	printf("\n");
}
