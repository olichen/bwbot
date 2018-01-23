#include "expansionhandler.h"

ExpansionHandler::ExpansionHandler(int mineralcount)
	: numBases(1), numMineralPatch(mineralcount)
{
	//
}

void ExpansionHandler::init(int mineralcount) {
	numBases = 1;
	numMineralPatch = mineralcount;
}

void ExpansionHandler::expand(int mineralcount) {
	numBases++;
	numMineralPatch += mineralcount;
}

int ExpansionHandler::getMineralRate(int mineralminercount, char race) const {
	int baserate = getRaceMineralRate(race);
	if (mineralminercount <= numMineralPatch)
		return baserate;
	else if (mineralminercount <= numMineralPatch * 3)
		return ((240) * (mineralminercount - numMineralPatch) / (numMineralPatch * 2) + baserate * (numMineralPatch * 3 - mineralminercount) / (numMineralPatch * 2));
	else
		return (240 * mineralminercount / numMineralPatch * 3);
	return baserate;
}

int ExpansionHandler::getRaceMineralRate(char race) const {
	if (race=='t')
		return 176;
	if (race=='z')
		return 172;
	if (race=='p')
		return 169;
	throw BadRace();
}

int ExpansionHandler::getGasRate() const {
	return 111;
}
