#include "build.h"
#include "unittree.h"
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

//game loop
void Build::init()
{
	//testing stuff
	//Unit test("Terran SCV",50,0,300,1,0,"Terran Command Center","Terran Command Center");
	//test.init(test, test);
	UnitTree test;
	test.addUnit("Terran SCV",50,0,300,1,0,"Terran Command Center","Terran Command Center");
	test.addUnit("Terran Command Center",400,0,1800,0,10,"Terran SCV","Terran SCV");
	test.init();


	typedef std::chrono::milliseconds ms;
	typedef std::chrono::nanoseconds ns;
	typedef std::chrono::high_resolution_clock clock;

	//framerate (16ms is 60fps, about 2.6x time)
	const ns timestep = std::chrono::duration_cast<ns>(ms(16));

	auto time_start = clock::now();
	ns lag(0);

	while(true)
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

void Build::update()
{
	resources.nextFrame();
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
