// build.cpp
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
	//load initial units
	loadRace('t');
	run();
}

//game loop
void Build::run()
{
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::nanoseconds ns;
	typedef std::chrono::high_resolution_clock clock;

	//framerate (10ms is 100fps, about 4x time)
	const ns timestep = std::chrono::duration_cast<ns>(ms(10));

	auto time_start = clock::now();
	ns lag(0);

	while(cResources.getFrame() <= 400)
	{
		auto time_delta = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<ns>(time_delta);

		while(lag >= timestep)
		{
			lag -= timestep;

			//update
			update();

			//print
			printResources();
		}
	}
}

void Build::loadRace(char race)
{
	cUnitTree.loadRace('t');
	if (race == 't')
	{
		Unit &unit = cUnitTree.findUnit("Terran SCV");
		cUnitList.initUnit(unit, 4);
		unit = cUnitTree.findUnit("Terran Command Center");
		cUnitList.initUnit(unit);
	}
}

void Build::update()
{
	cResources.nextFrame();
	cUnitList.update();
}

void Build::printResources()
{
	printf(" Frame |  Min  |  Gas  | Supply\n");
	printf("%6d |", cResources.getFrame());
	printf("%5d  |", cResources.getMinerals());
	printf("%5d  |", cResources.getGas());
	printf("%4d/%d", cResources.getSupply(), cResources.getSupplyMax());
	printf("\n");
}
