#include<iostream>
#include"FilesReading.h"
#include"Structs.h"
#include"GateSimulator.h"
using namespace std;



// Merge function for StimStruct object based on Delay
void merge(StimStruct& stim, int left, int mid, int right)           //Merge sort function edited by chat gpt to accomodate our specific needs in regards to vectors used

{
	int n1 = mid - left + 1; // Size of left subarray
	int n2 = right - mid;     // Size of right subarray

	// Create temporary vectors to hold the left and right subarrays
	vector<int> L_Delay(n1), R_Delay(n2);
	vector<string> L_inputVariables(n1), R_inputVariables(n2);
	vector<bool> L_status(n1), R_status(n2);
	vector<bool> L_changed(n1), R_changed(n2); // New vector for changed

	// Copy data to temporary vectors
	for (int i = 0; i < n1; i++) {
		L_Delay[i] = stim.Delay[left + i];
		L_inputVariables[i] = stim.inputVariables[left + i];
		L_status[i] = stim.status[left + i];
		L_changed[i] = stim.changed[left + i]; // Copy changed elements
	}
	for (int j = 0; j < n2; j++) {
		R_Delay[j] = stim.Delay[mid + 1 + j];
		R_inputVariables[j] = stim.inputVariables[mid + 1 + j];
		R_status[j] = stim.status[mid + 1 + j];
		R_changed[j] = stim.changed[mid + 1 + j]; // Copy changed elements
	}

	// Merge the temporary vectors back into stim.Delay, stim.inputVariables, stim.status, and stim.changed
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L_Delay[i] <= R_Delay[j]) {
			stim.Delay[k] = L_Delay[i];
			stim.inputVariables[k] = L_inputVariables[i];
			stim.status[k] = L_status[i];
			stim.changed[k] = L_changed[i]; // Swap corresponding changed element
			i++;
		}
		else {
			stim.Delay[k] = R_Delay[j];
			stim.inputVariables[k] = R_inputVariables[j];
			stim.status[k] = R_status[j];
			stim.changed[k] = R_changed[j]; // Swap corresponding changed element
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[], if any
	while (i < n1) {
		stim.Delay[k] = L_Delay[i];
		stim.inputVariables[k] = L_inputVariables[i];
		stim.status[k] = L_status[i];
		stim.changed[k] = L_changed[i]; // Copy remaining changed element
		i++;
		k++;
	}

	// Copy the remaining elements of R[], if any
	while (j < n2) {
		stim.Delay[k] = R_Delay[j];
		stim.inputVariables[k] = R_inputVariables[j];
		stim.status[k] = R_status[j];
		stim.changed[k] = R_changed[j]; // Copy remaining changed element
		j++;
		k++;
	}
}

// Merge Sort function for StimStruct object based on Delay
void mergeSort(StimStruct& stim, int left, int right)                    //part of the merge sort algorithm
{
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

void getLogic(LibStruct lib, LogicGate s)            //function that uses Lib file struct to match the logic of a gate with one of the logic expressions in the lib file

{
	for (int i = 0; i < lib.GatesNames.size(); i++)
	{
		if (s.type == lib.GatesNames[i])
		{
			s.logic = lib.Logic[i];
		}
	}
}

bool evaluateGate(string s, vector<bool> inp)    //functiont that uses the gate evaluator to evaluate outputs based on a vector of inputs
{
	LogicGateExpressionEvaluator evaluate;
	return evaluate.evaluateExpression(s, inp);
}




int main()
{


	FilesReading test;
	string libFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_5/Circuit_5_LIB.lib";    //file locations, make sure you change them to work on your machine
	string cirFileName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_5/Circuit_5_CIR.cir";
	string stimFileName ="C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_5/Circuit_5_STIM.stim";
	string OutName = "C:/Users/mosta/Desktop/AUC/DD1/Project/TestCircuit_5/Circuit_output.sim";      //the sim file that will be produced



	test.ReadLibFile(libFileName);
	test.ReadCirFile(cirFileName);    //here the readFile class starts reading the files and storing data
	test.ReadStimFile(stimFileName);


	test.PrintLib();
	test.PrintCir();    //part of the debugging process, functions that displays whats stored in each file struct
	test.PrintStim();
	test.PrintGates();




	for (int i = 0; i < test.gates.size(); i++)        //the main part of the program. This is used to evaluate each logic gate and decide its output and time stamp and stores them in their appropriate vectors
	{
		int counter = 0;
		int maxDelay = INT_MIN;   //integer to store the maximum delay of all the inputs

		for (int j = 0; j < test.gates[i].inputNames.size(); j++)    //loop to go over all the gates
		{


			for (int k = 0; k < test.stim.inputVariables.size(); k++)    //loop that goes over all the known variable 
			{

				cout << test.gates[i].inputNames[j] << "    " << test.stim.inputVariables[k] << "  " << test.stim.status[k] << endl;     //part of the debugging process
				if (test.gates[i].inputNames[j] == test.stim.inputVariables[k]) //if we find a matching input for the logic gate
				{
					if (test.stim.Delay[k] > maxDelay)
					{
						maxDelay = test.stim.Delay[k];        //we record the max delay
					}
					test.gates[i].inputs[j] = test.stim.status[k];  //we change the status of the logic gate input value
					counter++;




					bool temporayStore = test.gates[i].result;
					/*for (int u = 0; u < test.gates[i].inputs.size(); u++)
					{
						cout << test.gates[i].inputs[u] << "  ";
					}*/
					int StoreTime;                                                    //here we calculate the time stamp, evaluate the output and pushes them to their appropriate vectors
					StoreTime = test.gates[i].timeStamp;
					test.gates[i].timeStamp = maxDelay + test.gates[i].delay;
					test.gates[i].result = evaluateGate(test.gates[i].logic, test.gates[i].inputs);
					test.stim.addInputVariable(test.gates[i].OutputName);
					test.stim.addStatus(test.gates[i].result);
					test.stim.addDelay(test.gates[i].timeStamp);
					if (test.gates[i].result == temporayStore)     //if the output didnt change, the corresponding change variable in the change vetor is set to false so we dont include it in sim file
					{
						test.stim.changed.push_back(false);
					}
					else
						test.stim.changed.push_back(true);

					if (((test.gates[i].timeStamp - test.gates[i].delay) < StoreTime) && (StoreTime != -1) && (test.gates[i].result != temporayStore))  //this is part of the second implementation, if the current
					{                                                                                                         //interferes with an old output thats still processing the old one will be deleted
						for (int l = test.stim.inputVariables.size() - 2; l >= 0; l--)
						{
							if (test.stim.inputVariables[l] == test.gates[i].OutputName)
							{
								//test.stim.changed[l] = false; //this is the implementation using the second way, remve the comment and it will work    
							}
						}
					}
					if (counter == test.gates[i].inputNames.size())
						break;

				}
			}

		}
	}


	//test.PrintGates();


	mergeSort(test.stim, 0, test.stim.Delay.size() - 1);   //sorting the variables according to time stamp


	for (int i = 0; i < test.stim.Delay.size(); i++)  //part of the debugging process
	{
		cout << test.stim.Delay[i] << ", " << test.stim.inputVariables[i] << ", " << test.stim.status[i] << endl;
	}


	ofstream fileOutput;
	fileOutput.open(OutName);

	for (int i = 0; i < test.stim.Delay.size(); i++)
	{
		
		
		if (test.stim.changed[i])
		{
			if (i < test.stim.Delay.size() - 1)
			{                                                                                                //if there 2 outputs at exactly the same time, take the one that was evaluated later
				if ((test.stim.Delay[i] == test.stim.Delay[i + 1]) && (test.stim.inputVariables[i] == test.stim.inputVariables[i + 1]) && (test.stim.changed[i + 1]))
				{
					i++;
				}
			}

			
			string store = "";
			store += to_string(test.stim.Delay[i]) + ", " + test.stim.inputVariables[i] + ", " + to_string(test.stim.status[i]);
			fileOutput << store << endl;
		}
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
