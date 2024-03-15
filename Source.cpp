#include<iostream>
#include"FilesReading.h"
#include"Structs.h"
#include"GateSimulator.h"
using namespace std;




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

bool evaluateGate(string s, bool x, bool y)
{
	LogicGateExpressionEvaluator evaluate;
	return evaluate.evaluateExpression(s, x, y);
}
int main()
{
	FilesReading test;
	string libFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_4/Circuit_4_LIB.lib";
	string cirFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_4/Circuit_4_CIR.cir";
	string stimFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_4/Circuit_4_STIM.stim";



	test.ReadLibFile(libFileName);
	test.ReadCirFile(cirFileName);
	test.ReadStimFile(stimFileName);

	test.PrintLib();
	test.PrintCir();
	test.PrintStim();
	test.PrintGates();
	for (int i = 0; i < test.gates.size(); i++)
	{
		int counter = 0;
		for (int j = 0; j < test.gates[i].inputNames.size(); j++)
		{
		

			for (int k = 0; k < test.stim.inputVariables.size(); k++)
			{
				if (test.gates[i].inputNames[j] == test.stim.inputVariables[k])
				{
					test.gates[i].inputs[j] = test.stim.status[k];
					counter++;
					if (counter == test.gates[i].inputs.size())
					{
						test.gates[i].result = evaluateGate(test.gates[i].logic, test.gates[i].inputs[0], test.gates[i].inputs[1]);
						test.stim.addInputVariable(test.gates[i].OutputName);
						test.stim.addStatus(test.gates[i].result);
					}
				}
			}
			
		}
	}
	test.PrintGates();

	/*for (int z = 0; z < test.gates[i].inputNames.size(); z++)
	{
		if (test.gates[i].inputNames[z] == test.stim.inputVariables[j])
		{
			test.gates[i].inputs.push_back(test.stim.status[j]);
			counter++;
		}
	}
	if (test.gates[i].inputNames.size() == counter)
	{

		test.gates[i].result = evaluateGate(test.gates[i].logic, );
		for (int l = 0; l < test.gates.size(); l++)
		{
			if (test.gates[l].)
		}
	}*/

	


}
