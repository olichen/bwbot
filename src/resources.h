#pragma once

class Resources
{
	public:
		Resources();

		int getMinerals() { return m_minerals; }
		int getGas() { return m_gas; }
		int getSupply() { return m_supply; }
		int getSupplyMax() { return m_supply_max; }
		int getFrame() { return m_frame; }

		// increment minerals, gas, supply, frame
		void addMinerals(int minerals = 8) { m_minerals += minerals; }
		void addGas(int gas = 8) { m_gas += gas; }
		void addSupplyMax(int supply = 8) { m_supply += supply; }
		void addFrame(int frame = 1) { m_frame += frame; }

		void useMinerals(int minerals) { m_minerals -= minerals; }
		void useGas(int gas) { m_gas -= gas; }
		void useSupply(int supply) { m_supply += supply; }

	private:
		int m_minerals, m_gas, m_supply, m_supply_max, m_frame;
};
