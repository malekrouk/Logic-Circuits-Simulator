#pragma once
#include<vector>;
#include<string>
using namespace std;
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
};

struct CircuitStruct
{
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
	
};
struct StimStruct
{
	vector<int> Delay;
	vector<char> inputVariables;
	vector<bool> status;
	void addDelay(int x)
	{
		Delay.push_back(x);
	}
	void addInputVariable(char c)
	{
		inputVariables.push_back(c);
	}
	void addStatus(bool x)
	{
		status.push_back(x);
	}

};
