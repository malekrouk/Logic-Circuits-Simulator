#include<iostream>
#include"FilesReading.h"
#include"Structs.h"
using namespace std;
int main()
{
	FilesReading test;
	string libFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_2/Circuit_2_LIB.lib";
	string cirFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_2/Circuit_2_CIR.cir";
	ifstream hh;
	test.ReadLibFile(libFileName);

	//for (int i = 0; i < 4; i++)
	//{
	//	cout << test.Lib.InputNum[i] << endl;
	//}
	test.ReadCirFile(cirFileName);

}
