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

		LogicGate x;
		int inputCounter = 1;
		CirFile >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());

		x.name = temp;
		cir.addComponentName(temp);


		CirFile >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());

		if ((temp[temp.size() - 1] <= 57) && (temp[temp.size() - 1] >= 48))
			inputCounter = (temp[temp.size() - 1]) - '0';


		x.type = temp;

		for (int i = 0; i < Lib.GatesNames.size(); i++)
		{
			if (Lib.GatesNames[i] == temp)
			{
				cir.logic.push_back(Lib.Logic[i]);
				x.logic = Lib.Logic[i];
				break;
			}
		}



		cir.addType(temp);
		CirFile >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());

		x.OutputName = temp;
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
		x.inputNames = soy;
		for (int i = 0; i < soy.size(); i++)
		{
			x.inputs.push_back(0);
		}
		gates.push_back(x);
	}



}

void FilesReading::ReadStimFile(string s)
{
	ifstream FileOpen;
	FileOpen.open(s);
	string temp;
	while (!FileOpen.eof())
	{
		FileOpen >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		stim.addDelay(stoi(temp));

		FileOpen >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		stim.addInputVariable(temp);

		FileOpen >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		bool x=false;
		if (temp == "1")
		{
			x = true;
		}
		stim.addStatus(x);


	}





	


}

void FilesReading::PrintLib()
{
	Lib.PrintLib();
}


void FilesReading::PrintCir()
{
	cir.PrintCir();
}

void FilesReading::PrintStim()
{
	stim.PrintSim();
}

void FilesReading::PrintGates()
{
	for (int i = 0; i < gates.size(); i++)
	{
		cout << gates[i].name << "  " << gates[i].type << "  " << gates[i].logic << "  " << gates[i].OutputName << "  ";
		for (int j = 0;j < gates[i].inputNames.size(); j++)
		{
			cout << gates[i].inputNames[j]<<"  ";
		}
		cout << "Output : " << gates[i].result;
		cout << endl<<endl;
	}


}

