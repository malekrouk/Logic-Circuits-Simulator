#include<iostream>
#include"FilesReading.h"
#include"Structs.h"
#include"GateSimulator.h"
using namespace std;



// Merge function for StimStruct object based on Delay
void merge(StimStruct& stim, int left, int mid, int right) {
	int n1 = mid - left + 1; // Size of left subarray
	int n2 = right - mid;     // Size of right subarray

	// Create temporary vectors to hold the left and right subarrays
	vector<int> L_Delay(n1), R_Delay(n2);
	vector<string> L_inputVariables(n1), R_inputVariables(n2);
	vector<bool> L_status(n1), R_status(n2);

	// Copy data to temporary vectors
	for (int i = 0; i < n1; i++) {
		L_Delay[i] = stim.Delay[left + i];
		L_inputVariables[i] = stim.inputVariables[left + i];
		L_status[i] = stim.status[left + i];
	}
	for (int j = 0; j < n2; j++) {
		R_Delay[j] = stim.Delay[mid + 1 + j];
		R_inputVariables[j] = stim.inputVariables[mid + 1 + j];
		R_status[j] = stim.status[mid + 1 + j];
	}

	// Merge the temporary vectors back into stim.Delay, stim.inputVariables, and stim.status
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L_Delay[i] <= R_Delay[j]) {
			stim.Delay[k] = L_Delay[i];
			stim.inputVariables[k] = L_inputVariables[i];
			stim.status[k] = L_status[i];
			i++;
		}
		else {
			stim.Delay[k] = R_Delay[j];
			stim.inputVariables[k] = R_inputVariables[j];
			stim.status[k] = R_status[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[], if any
	while (i < n1) {
		stim.Delay[k] = L_Delay[i];
		stim.inputVariables[k] = L_inputVariables[i];
		stim.status[k] = L_status[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[], if any
	while (j < n2) {
		stim.Delay[k] = R_Delay[j];
		stim.inputVariables[k] = R_inputVariables[j];
		stim.status[k] = R_status[j];
		j++;
		k++;
	}
}

// Merge Sort function for StimStruct object based on Delay
void mergeSort(StimStruct& stim, int left, int right) {
	if (left < right) {
		// Find the middle point
		int mid = left + (right - left) / 2;

		// Recursively sort first and second halves
		mergeSort(stim, left, mid);
		mergeSort(stim, mid + 1, right);

		// Merge the sorted halves
		merge(stim, left, mid, right);
	}
}

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

bool evaluateGate(string s, vector<bool> inp)
{
	LogicGateExpressionEvaluator evaluate;
	return evaluate.evaluateExpression(s, inp);
}




int main()
{


	FilesReading test;
	string libFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_2/Circuit_2_LIB.lib";
	string cirFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_2/Circuit_2_CIR.cir";
	string stimFileName ="C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_2/Circuit_2_STIM.stim";



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
		int maxDelay = INT_MIN;
		for (int j = 0; j < test.gates[i].inputNames.size(); j++)
		{
		

			for (int k = 0; k < test.stim.inputVariables.size(); k++)
			{

				cout << test.gates[i].inputNames[j] << "    " << test.stim.inputVariables[k] << "  " << test.stim.status[k]<< endl;
				if (test.gates[i].inputNames[j] == test.stim.inputVariables[k])
				{
					if (test.stim.Delay[k] > maxDelay)
					{
						maxDelay = test.stim.Delay[k];
					}
					test.gates[i].inputs[j] = test.stim.status[k];
					counter++;
					if (counter == test.gates[i].inputs.size())
					{


						/*for (int u = 0; u < test.gates[i].inputs.size(); u++)
						{
							cout << test.gates[i].inputs[u] << "  ";
						}*/
						test.gates[i].timeStamp = maxDelay + test.gates[i].delay;
						test.gates[i].result = evaluateGate(test.gates[i].logic, test.gates[i].inputs);
						test.stim.addInputVariable(test.gates[i].OutputName);
						test.stim.addStatus(test.gates[i].result);
						test.stim.addDelay(test.gates[i].timeStamp);


					}
					break;
				}
			}
			
		}
	}


	//test.PrintGates();


	mergeSort(test.stim, 0, test.stim.Delay.size()-1);


	for (int i = 0; i < test.stim.Delay.size(); i++)
	{
		cout << test.stim.Delay[i] << ", " << test.stim.inputVariables[i] << ", "<<test.stim.status[i]<<endl;
	}


	ofstream fileOutput;
	fileOutput.open("C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_2/Circuit_output.sim");

		for (int i = 0; i < test.stim.Delay.size(); i++)
		{
			string store="";
			store += to_string(test.stim.Delay[i]) + ", " + test.stim.inputVariables[i] + ", " +to_string(test.stim.status[i]);
			fileOutput << store << endl;
		}

	//LogicGateExpressionEvaluator evaluate;
	//
	//    string expression = "~(i1|i2)";
	//    int num_variables = 2; // Up to i4
	//    vector<bool> inputs(num_variables);
	//    inputs[0] = 1;
	//    inputs[1] = 1;
	//	bool result1 = evaluate.evaluateExpression(expression, inputs);
	//	cout << result1;

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
