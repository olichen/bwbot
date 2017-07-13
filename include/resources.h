#pragma once

class Resources
{
	public:
		Resources(int mineralPatches = 9, int gasGeysers = 1, char race = 't');

		void addExpansion(int mineralPatches = 7, int gasGeysers = 1);

		int getMinerals() const { return mMinerals; }
		int getGas() const { return mGas; }
		int getSupply() const { return mSupply; }
		int getAvailableSupply() const { return mSupplyMax - mSupply; }
		int getSupplyMax() const { return mSupplyMax; }
		int getFrame() const { return mFrame; }
		int getMineralPatches() const { return mMineralPatches; }
		int getGasGeysers() const { return mGasGeysers; }
		int getBaseMineRate() const;
		char getRace() const { return mRace; }
		void clear() { mMinerals = 0; mGas = 0; mSupply = 0; mSupplyMax = 0; mFrame = 0; }
		void reset(int mineralPatches = 9, int gasGeysers = 1);

		// increment minerals, gas, supply, frame
		void addMinerals(int minerals = 8) { mMinerals += minerals; }
		void addGas(int gas = 8) { mGas += gas; }
		void addSupplyMax(int supply = 8) { mSupplyMax += supply; }
		void nextFrame(int frame = 1) { mFrame += frame; }
		void setRace(char race = 't') { mRace = race; }

		void useMinerals(int minerals) { mMinerals -= minerals; }
		void useGas(int gas) { mGas -= gas; }
		void useSupply(int supply) { mSupply += supply; }

	private:
		int mMinerals, mGas, mSupply, mSupplyMax, mFrame;
		int mMineralPatches, mGasGeysers;
		char mRace;
};
