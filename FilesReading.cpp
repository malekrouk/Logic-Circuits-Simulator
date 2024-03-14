#include<iostream>
#include"FilesReading.h"
#include"Structs.h"
#include"GateSimulator.h"
using namespace std;


struct LogicGate
{
	string name;
	string type;
	string logic;
	vector<string> inputNames;
	vector<bool> inputs;
	string OutputName;
	bool result;

};

void getLogic(LibStruct lib, LogicGate s)
{
	for (int i = 0; i < lib.GatesNames.size(); i++)
	{
		if (s.type == lib.GatesNames[i])
		{
			s.logic = lib.Logic[i];
		}
	}
}
int main()
{
	FilesReading test;
	string libFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_4/Circuit_4_LIB.lib";
	string cirFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_4/Circuit_4_CIR.cir";
	string stimFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_4/Circuit_4_STIM.stim";

	/*ifstream hh;
	hh.open(libFileName);
	cout << hh.is_open();*/




	test.ReadLibFile(libFileName);
	//for (int i = 0; i < 4; i++)
	//{
	//	cout << test.Lib.InputNum[i] << endl;
	//}
	test.ReadCirFile(cirFileName);
	test.ReadStimFile(stimFileName);


	/*for (int i = 0; i < test.stim.Delay.size(); i++)
	{
		cout << test.stim.Delay[i]<<endl;
	}

	cout << endl;

	for (int i = 0; i < test.cir.Inputs.size(); i++)
	{
		cout << test.cir.Inputs[i]<<endl;
	}
	cout << endl << endl;
	for (int i = 0; i < test.cir.componentName.size(); i++)
	{
		cout << test.cir.componentName[i]<<endl;
	}*/



	vector<LogicGate> hello;
	for (int i = 0; i < test.cir.componentName.size();i++)
	{
		LogicGate testing1;
		testing1.name = test.cir.componentName[i];
		testing1.type = test.cir.type[i];
		testing1.inputNames = test.cir.GateInputs[i];
		getLogic(test.Lib, testing1);
		testing1.OutputName = test.cir.output[i];
		hello.push_back(testing1);
	}



	//for (int i = 0; i < hello.size(); i++)
	//{
	//	cout << hello[i].type<<endl;
	//}



	//for (int j = 0; j < test.stim.inputVariables.size(); j++)
	//{
	//	cout << test.stim.inputVariables[j];
	//}


	for (int i = 0; i < hello.size(); i++)
	{
		for (int j = 0; j < test.stim.inputVariables.size(); j++)
		{
			string s1 = "";
			s1 += test.stim.inputVariables[j];

			if (hello[i].inputNames[0] == s1)
				 hello[i].inputs.push_back(test.stim.status[j]);

			if (hello[i].inputNames[1] == s1)
				hello[i].inputs.push_back(test.stim.status[j]); 
		}
	}


	for (int k = 0; k < hello.size(); k++)
	{
		for (int i = 0; i < hello.size(); i++)
		{
			if (hello[i].inputNames.size() == hello[i].inputs.size())
			{
				LogicGateExpressionEvaluator evaluate;
				hello[i].result = evaluate.evaluateExpression(hello[i].logic, hello[i].inputs[0], hello[i].inputs[1]);

				//cout<< evaluate.evaluateExpression(hello[i].logic, hello[i].inputs[0], hello[i].inputs[1])<<"  ";

				for (int j = 0; j < hello.size(); j++)
				{
					for (int z = 0; z < hello[j].inputs.size(); z++)
					{
						if (hello[i].OutputName == hello[j].inputNames[z])
						{
							hello[j].inputs[z] = hello[i].result;
						//	cout << hello[j].inputs[z] << "  ";
						}
					}
				}
			}
		}
	}



	for (int i = 0; i < hello.size(); i++)
	{
		cout << hello[i].name << "  " << hello[i].type << "  " << hello[i].logic << "  ";
		for (int j = 0; j < hello[i].inputNames.size(); j++)
		{
			cout << hello[i].inputNames[j];
		}
	}
	//for (int i = 0; i < hello.size(); i++)
	//{

	//	cout << hello[i].name << "  " << hello[i].type << "  " << hello[i].logic << "  ";
	//	for (int j = 0; j < hello[i].inputs.size(); j++)
	//	{
	//		cout << hello[i].inputNames[j] << " " << hello[i].inputs[j]<<"      ";
	//	}
	//	cout << hello[i].OutputName << " " << hello[i].result<<"   ";
	//	cout << endl;
	//}

	//cout << hello[1].result;
	


	/*LogicGateExpressionEvaluator evaluate;
	bool i1, i2;
	i1 = test.stim.status[0];
	i2 = test.stim.status[1];
	string expression;

	i1 = false;
	i2 = false;
	expression = "i1&~i2";
	cout << "Result of " << expression << " with i1=" << i1 << " and i2=" << i2 << " is: " << evaluate.evaluateExpression(expression, i1, i2) << std::endl;

	expression = "~(i1|i2)";
	std::cout << "Result of " << expression << " with i1=" << i1 << " and i2=" << i2 << " is: " << evaluate.evaluateExpression(expression, i1, i2) << std::endl;

	expression = "i1&i2|~i1";
	std::cout << "Result of " << expression << " with i1=" << i1 << " and i2=" << i2 << " is: " << evaluate.evaluateExpression(expression, i1, i2) << std::endl;*/


}
