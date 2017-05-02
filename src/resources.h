class Resources {
	public:
		Resources();
		getMinerals();
		getGas();
		getSupply();
		getFrame();

		addMinerals(int minerals);
		addGas(int gas);
		addSupply(int supply);
		addFrame(int frame);
	private:
		int minerals, gas, supply, frame;
}
