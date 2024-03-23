#include "FilesReading.h"
#include <iostream>

void FilesReading::ReadLibFile(string s)
{
	ifstream LibFile;
	LibFile.open(s);

	if (!LibFile.is_open())
	{
		cout << "error opening Lib file, please recheck the name ";
		return;
	}

	while (!LibFile.eof())
	{
		string temp;
		LibFile >> temp;
		if (temp == "")  //if the file became empty(only have spaces or new lines
		{
			break;
		}
		//cout << temp << endl;

		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		FilesReading::Lib.addGateName(temp);
		LibFile >> temp;
		if (temp == "")  //if the file became empty(only have spaces or new lines
		{
			break;
		}
		//cout << temp << endl;

		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		Lib.addInputNum(stoi(temp));
		LibFile >> temp;
		if (temp == "")  //if the file became empty(only have spaces or new lines
		{
			break;
		}
		//cout << temp << endl;

		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		Lib.addLogic(temp);
		LibFile >> temp;
		if (temp == "")  //if the file became empty(only have spaces or new lines
		{
			break;
		}
		//cout << temp << endl;

		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		Lib.addDelay(stoi(temp));

	}


}

void FilesReading::ReadCirFile(string s)
{
	ifstream CirFile;
	CirFile.open(s);

	if (!CirFile.is_open())
	{
		cout << "error opening Cir file, please recheck the name ";
		return;
	}

	string temp;
	getline(CirFile, temp);
	//cout << temp << endl;
	CirFile >> temp;

	while (temp != "COMPONENTS:")
	{
		CirFile >> temp;
	//	cout << temp << endl;
		FilesReading::cir.addInput(temp[0]);
	}


	while (!CirFile.eof())
	{

		LogicGate x;
		int inputCounter = 1;
		CirFile >> temp;
		//cout << temp << endl;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());

		x.name = temp;
		cir.addComponentName(temp);


		CirFile >> temp;
		//cout << temp << endl;
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
				x.delay = Lib.Delay[i];
				break;
			}
		}



		cir.addType(temp);
		CirFile >> temp;
		//cout << temp << endl;
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
	if (!FileOpen.is_open())
	{
		cout << "error opening stim file, please recheck the name ";
		return;
	}
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
		if (x == true)
		{
			stim.changed.push_back(true);
		}
		else
			stim.changed.push_back(false);

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
		cout << "Output : " << gates[i].result<<"  "<< "Gate Delay : "<<gates[i].delay<<"  Time Stamp : "<<gates[i].timeStamp;
		cout << endl<<endl;
	}


}

