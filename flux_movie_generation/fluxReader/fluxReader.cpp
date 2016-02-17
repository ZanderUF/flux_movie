# include <iostream>
# include <fstream>
# include <string>
# include <queue>

#include "KenoUnit.h"

using namespace std;

bool is_numerical(char c)
{
	int cVal = int(c);

	if ((cVal >= 48 && cVal <= 57) || 					\
		 cVal == 43 || cVal == 45  || 					 \
		 cVal == 46 || cVal == 69) // digit, (.), (+/-), or E
	{
		return true;
	}
	else
	{
		return false;
	}
}

int* organizeInput(string command, int& size)
{
	int currentIndex = 0, \
		stringLength = command.length();

	if (stringLength == 0 || stringLength == 1)
	{
		return NULL;
	}

	queue<int> inputQ;

	string number = "";

	for (int i = 0; i < stringLength; i++)
	{
		if (int(command[i]) == 39) break; // the rest is commented out

		if (int(command[i]) != 32 && int(command[i]) != 9 && int(command[i]) != 10)			// if not a space, tab, or NL
		{
			if (is_numerical(command[i]))
			{
				number += command[i];
			}
			else
			{
				return NULL;
				//throw invalid_argument("Error: Character not accepted");
				//number = "";
				//break;												// This is to prevent any bad inputs slipping through the organizer and
			}//															affecting the list
		}
		else // it is a space
		{
			if (number != "")
			{
				inputQ.push(atoi(number.c_str()));
				currentIndex++;
				number = "";
			}
		}
	}

	if (number != "")
	{
		inputQ.push(atoi(number.c_str()));
		currentIndex++;
	}

	int* input = new int[currentIndex];

	for (int i = 0; i < currentIndex; i++)
	{
		input[i] = inputQ.front();
		inputQ.pop();
	}

	size = currentIndex;
		
	return input;
}

float* organizeFloatInput(string command, int& size)
{
	int currentIndex = 0, \
		stringLength = command.length();

	if (stringLength == 0 || stringLength == 1)
	{
		return NULL;
	}

	queue<float> inputQ;

	string number = "";

	for (int i = 0; i < stringLength; i++)
	{
		//if (int(command[i]) == 39) break; // the rest is commented out

		if (int(command[i]) != 32 && int(command[i]) != 9 && int(command[i]) != 10)			// if not a space, tab, or NL
		{
			if (is_numerical(command[i]))
			{
				number += command[i];
			}
		}
		else // it is a space
		{
			if (number != "")
			{
				inputQ.push(atof(number.c_str()));
				currentIndex++;
				number = "";
			}
		}
	}

	if (number != "")
	{
		inputQ.push(atof(number.c_str()));
		currentIndex++;
	}

	if (currentIndex == 0)
	{
		return NULL;
	}

	float* input = new float[currentIndex];

	for (int i = 0; i < currentIndex; i++)
	{
		input[i] = inputQ.front();
		inputQ.pop();
	}

	size = currentIndex;
		
	return input;
}

void printFluxesByUnit(queue<KenoUnit*> & units)
{
	ofstream output ("unitFluxes.out");
	KenoUnit* myUnit = new KenoUnit();

	if (output.is_open())
	{
		while (!units.empty())
		{
			myUnit = units.front();
			output << myUnit->getUnitNum() << " " << myUnit->getTotalFlux() << endl;
			cout << myUnit->getUnitNum() << " " << myUnit->getTotalFlux() << endl;
	  		units.pop();	
		}

		output.close();		
	}
}

int main()
{
	fstream keno_output ("_out000000000000000000");

	queue<KenoUnit*> units;

	if (keno_output.is_open())
	{
		string line;

		int size = 0;
		int lastRegion = 1;
		int crntUnit = 0;
		int igp = 0;
		int diff = 0;

		bool firstTake = false;
		bool secondTake = false;

		int* orgLine = NULL;
		float* fluxLine = NULL;
		float* fluxVals = NULL;
		int* regions = NULL;

		KenoUnit* myUnit = new KenoUnit();

		while (getline(keno_output, line))
		{
			if (line.find("**** fission densities ****") != string::npos)
			{
				firstTake = true;
			}
			else if (line.find(" writing fluxes to file flux.for.....") != string::npos)
			{
				firstTake = false;
				secondTake = true;
				myUnit->initialize(crntUnit, lastRegion);
				units.push(myUnit->getCopy()); // might still be pointing at smae object
				myUnit = new KenoUnit();
			}

			if (firstTake)
			{
				orgLine = organizeInput(line, size);

				if (orgLine != NULL)
				{
					if (size == 5)
					{
						if (orgLine[0] == 1)
						{
							crntUnit = orgLine[0];
							lastRegion = orgLine[1];
						}
						else
						{
							myUnit->initialize(crntUnit, lastRegion);
							units.push(myUnit->getCopy());
							myUnit = new KenoUnit();
							crntUnit = orgLine[0];
							lastRegion = orgLine[1];
						}
					}
					else if (size == 4)
					{
						lastRegion = orgLine[0];
					}
					else
					{
						cout << "What?" << endl;
						break;
					}
				}
			}
			else if (secondTake)
			{
				fluxLine = organizeFloatInput(line, size);

				if (line.find(" groups") != string::npos)
				{
					igp = fluxLine[1];
				}
				else if (line.find("Global Unit") != string::npos)
				{
					crntUnit = 1;
					myUnit = units.front()->getCopy();
					units.pop();
				}
				else if (line.find("for Unit") != string::npos && fluxLine[0] != crntUnit)
				{
					myUnit->setFluxes(fluxVals);
					units.push(myUnit->getCopy());
					crntUnit = fluxLine[0];
					myUnit = units.front()->getCopy();
					units.pop();
					//cout << "Found Unit " << crntUnit << endl;
				}
				else if (line.find(" region ") != string::npos)
				{
					regions = new int[size];

					diff = fluxLine[size-1] - fluxLine[0];

					for (int i = 0; i < size; i++)
					{
						regions[i] = (int) fluxLine[i];
					}

					if (regions[0] == 1)
					{					
						fluxVals = new float[myUnit->getNumRegions()];
	
						for (int i = 0; i < myUnit->getNumRegions(); i++)
						{
							fluxVals[i] = 0.0;
						}
					}
				}
				else if (line.find("frequency for generations") != string::npos)
				{
					myUnit->setFluxes(fluxVals);
					units.push(myUnit);
					break;
				}
				else if (fluxLine != NULL && size > 1)
				{	
					for (int i = 0; i <= diff; i++)
					{
						fluxVals[regions[i] - 1] += fluxLine[(2*i) + 1];
					}
				}
			}
		}

		printFluxesByUnit(units);

/*		while (!units.empty())
		{
			myUnit = units.front();

			cout << "Unit " << myUnit->getUnitNum() << endl;
			myUnit->printAllFluxes();
			cout << endl << endl;

			units.pop();			
		}*/
	}

	keno_output.close();

	return 0;
}
