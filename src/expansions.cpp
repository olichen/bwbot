#include "expansions.h"

Expansions::Expansions(int mineralcount)
	: numBases(1), numMineralPatch(mineralcount)
{
	//
}

void Expansions::init(int mineralcount) {
	numBases = 1;
	numMineralPatch = mineralcount;
}

void Expansions::expand(int mineralcount) {
	numBases++;
	numMineralPatch += mineralcount;
}

int Expansions::getMineralRate(int mineralminercount, char race) const {
	int baserate = getRaceMineralRate(race);
	if (mineralminercount <= numMineralPatch)
		return baserate;
	else if (mineralminercount <= numMineralPatch * 3)
		return ((240) * (mineralminercount - numMineralPatch) / (numMineralPatch * 2) + baserate * (numMineralPatch * 3 - mineralminercount) / (numMineralPatch * 2));
	else
		return (240 * mineralminercount / numMineralPatch * 3);
	return baserate;
}

int Expansions::getRaceMineralRate(char race) const {
	if (race=='t')
		return 176;
	if (race=='z')
		return 172;
	if (race=='p')
		return 169;
	throw BadRace();
}

int Expansions::getGasRate() const {
	return 111;
}
