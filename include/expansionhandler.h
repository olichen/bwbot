#pragma once
#include "exceptions.h"

class ExpansionHandler {
	public:
		ExpansionHandler(int mineralcount = 9);
		void init(int mineralcount = 9);
		void expand(int mineralcount = 7);

		int getMineralRate(int workercount, char race) const;
		int getRaceMineralRate(char race) const;
		int getGasRate() const;

	private:
		int numBases, numMineralPatch;
};
