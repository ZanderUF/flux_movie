# include <iostream>
# include <fstream>
# include <string>

using namespace std;

class KenoUnit
{
	int unit;
	int numRegions;
	int* regions;
	float* fluxes;
	float totalFlux;

public:

	KenoUnit() {}

	~KenoUnit()
	{
		regions = NULL;
		fluxes = NULL;
	}

	void initialize(int unit, int numRegions)
	{
		this->unit = unit;
		this->numRegions = numRegions;
		
		regions = new int[numRegions];

		fluxes = new float[numRegions];

		for (int i = 0; i < numRegions; i++)
		{
			regions[i] = i+1;	// regions are stored from zero, but labeled from one
			fluxes[i] = 0.0;
		}

		totalFlux = 0.0;
	}

	KenoUnit* getCopy() const
	{
		KenoUnit* copy = new KenoUnit();
		copy->initialize(unit, numRegions);
		copy->setFluxes(fluxes);
		return copy;
	}

// get

	int getUnitNum() const
	{
		return unit;
	}

	int getNumRegions() const
	{
		return numRegions;
	}

	float getTotalFlux() const
	{
		return totalFlux;
	}

// set

	void setFluxes(float* flvals) // this also calculates the total flux for the unit
	{
		for (int i = 0; i < numRegions; i++)
		{
			fluxes[i] = flvals[i];
		}

		for (int i = 0; i < numRegions; i++)
		{
			totalFlux += fluxes[i];
		}

		//cout << "Unit:" << unit << " Total Flux: " << totalFlux << endl;
		//cout << endl;
	}

// print

	void printAllFluxes() const
	{
		for (int i = 0; i < numRegions; i++)
		{
			cout << "Region: " << i+1 << " Flux: " << fluxes[i] << endl;
		}

		cout << "Total Flux for Unit " << unit << ": " << totalFlux << endl;
	}

};
