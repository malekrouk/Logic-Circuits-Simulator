#include<iostream>
#include"FilesReading.h"
#include"Structs.h"
using namespace std;
int main()
{
	FilesReading test;
	string libFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_2/Circuit_2_LIB.lib";
	string cirFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_2/Circuit_2_CIR.cir";
	string stimFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_2/Circuit_2_STIM.stim";

	ifstream hh;
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

}
