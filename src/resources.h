class Resources
{
	public:
		Resources();

		int getMinerals() { return m_minerals; }
		int getGas() { return m_gas; }
		int getSupply() { return m_supply; }
		int getFrame() { return m_frame; }

		// increment minerals, gas, supply, frame
		void addMinerals(int minerals = 8) { m_minerals += minerals; }
		void addGas(int gas = 8) { m_gas += gas; }
		void addSupply(int supply = 8) { m_supply += supply; }
		void addFrame(int frame = 1) { m_frame += frame; }
	private:
		int m_minerals, m_gas, m_supply, m_frame;
};
