#include "FilesReading.h"
#include <iostream>

void FilesReading::ReadLibFile(string s)
{
	ifstream LibFile;
	LibFile.open(s);
	while (!LibFile.eof())
	{
		string temp;
		LibFile >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		FilesReading::Lib.addGateName(temp);
		LibFile >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		Lib.addInputNum(stoi(temp));
		LibFile >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		Lib.addLogic(temp);
		LibFile >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		Lib.addDelay(stoi(temp));

	}


}

void FilesReading::ReadCirFile(string s)
{
	ifstream CirFile;
	CirFile.open(s);
	string temp;
	getline(CirFile, temp);
	CirFile >> temp;

	while (temp != "COMPONENTS:")
	{
		CirFile >> temp;
		FilesReading::cir.addInput(temp[0]);
	}


	while (!CirFile.eof())
	{
		int inputCounter = 1;
		CirFile >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		cir.addComponentName(temp);
		CirFile >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());

		if ((temp[temp.size() - 1] <= 57) && (temp[temp.size() - 1] >= 48))
			inputCounter = (temp[temp.size() - 1]) - '0';


		cir.addType(temp);
		CirFile >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		cir.addOutput(temp);

		vector<string> soy;
		while (inputCounter != 0)
		{
			CirFile >> temp;
			temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
			inputCounter--;
			soy.push_back(temp);
		}
		cir.addGateInput(soy);
	}



}
