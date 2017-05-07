// resources.h
#pragma once

class Resources
{
	public:
		Resources(int mineralPatches = 9, int gasGeysers = 1);

		void addExpansion(int mineralPatches = 7, int gasGeysers = 1);

		int getMinerals() { return mMinerals; }
		int getGas() { return mGas; }
		int getSupply() { return mSupply; }
		int getAvailableSupply() { return mSupplyMax - mSupply; }
		int getSupplyMax() { return mSupplyMax; }
		int getFrame() { return mFrame; }
		int getMineralPatches() { return mMineralPatches; }
		int getGasGeysers() { return mGasGeysers; }

		// increment minerals, gas, supply, frame
		void addMinerals(int minerals = 8) { mMinerals += minerals; }
		void addGas(int gas = 8) { mGas += gas; }
		void addSupplyMax(int supply = 8) { mSupplyMax += supply; }
		void nextFrame(int frame = 1) { mFrame += frame; }

		void useMinerals(int minerals) { mMinerals -= minerals; }
		void useGas(int gas) { mGas -= gas; }
		void useSupply(int supply) { mSupply += supply; }

	private:
		int mMinerals, mGas, mSupply, mSupplyMax, mFrame;
		int mMineralPatches, mGasGeysers;
};
