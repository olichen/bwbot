#pragma once

class Resources
{
	public:
		Resources();

		int getMinerals() { return mMinerals; }
		int getGas() { return mGas; }
		int getSupply() { return mSupply; }
		int getSupplyMax() { return mSupplyMax; }
		int getFrame() { return mFrame; }

		// increment minerals, gas, supply, frame
		void addMinerals(int minerals = 8) { mMinerals += minerals; }
		void addGas(int gas = 8) { mGas += gas; }
		void addSupplyMax(int supply = 8) { mSupply += supply; }
		void addFrame(int frame = 1) { mFrame += frame; }

		void useMinerals(int minerals) { mMinerals -= minerals; }
		void useGas(int gas) { mGas -= gas; }
		void useSupply(int supply) { mSupply += supply; }

	private:
		int mMinerals, mGas, mSupply, mSupplyMax, mFrame;
};
