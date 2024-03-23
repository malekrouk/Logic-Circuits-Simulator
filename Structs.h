#pragma once
#include<iostream>
#include<vector>;
#include<string>
using namespace std;

struct LogicGate
{
	string name;
	string type;
	string logic;
	vector<string> inputNames;
	vector<bool> inputs;
	string OutputName;
	bool result = 0;
	int timeStamp=-1;
	int delay=-1;


};


struct LibStruct
{
	std::vector<std::string> GatesNames;
	std::vector<int> InputNum;
	std::vector<std::string> Logic;
	std::vector<int> Delay;
	void addGateName(std::string s)
	{
		GatesNames.push_back(s);
	}
	void addInputNum(int n)
	{
		InputNum.push_back(n);
	}
	void addLogic(std::string s)
	{
		Logic.push_back(s);
	}
	void addDelay(int x)
	{
		Delay.push_back(x);
	}

	void PrintLib()
	{


		for (int i = 0; i < GatesNames.size(); i++)
		{
			cout << GatesNames[i] << "  Input variables = " << InputNum[i] << "   Logic = " << Logic[i] << "   Delay = " << Delay[i] << endl;
		}
		cout << GatesNames.size() << "  " << InputNum.size() << "  " << Logic.size() << "  " << Delay.size() << endl;


	}
};

struct CircuitStruct
{
	vector<string> logic;
	vector<char> Inputs;
    vector<string> componentName;
	vector<string> type;
	vector<string> output;
	vector<vector<string>> GateInputs;
	void addInput(char c)
	{
		Inputs.push_back(c);
	}
	void addComponentName(string s)
	{
		componentName.push_back(s);
	}
	void addType(string s)
	{
		type.push_back(s);
	}
	void addOutput(string s)
	{
		output.push_back(s);
	}
	void addGateInput(vector<string> s)
	{
		GateInputs.push_back(s);
	}

	void PrintCir()
	{
		//cout << "HELLO  " << GateInputs.size() << "    " << componentName.size()<<endl;
		for (int i = 0; i < componentName.size(); i++)
		{
			cout << componentName[i] << "  " << type[i] << "   " << output[i] << "   ";
			for (int j = 0; j < GateInputs[i].size(); j++)
			{
				cout << GateInputs[i][j] << "  ";
			}
			cout << endl;
		}
		cout << this->type.size() <<"  "<< output.size() <<"  "<< componentName.size() <<"  "<< Inputs.size() <<"  "<<GateInputs.size()<<endl;
	}
	
};
struct StimStruct
{
	vector<int> Delay;
	vector<string> inputVariables;
	vector<bool> status;
	vector<bool> changed;
	void addDelay(int x)
	{
		Delay.push_back(x);
	}
	void addInputVariable(string c)
	{
		inputVariables.push_back(c);
	}
	void addStatus(bool x)
	{
		status.push_back(x);
	}

	void PrintSim()
	{
		for (int i = 0; i < Delay.size(); i++)
		{
			cout << Delay[i] << "  " << inputVariables[i] << "  " << status[i] << endl;
		}
		cout << Delay.size() << "  " << inputVariables.size() << "  " << status.size() << endl;
	}

};
