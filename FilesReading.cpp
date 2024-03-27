#include "FilesReading.h"
#include <iostream>

void FilesReading::ReadLibFile(string s)  //function to read contents from a lib file and store it in vectors
{
	ifstream LibFile;
	LibFile.open(s);

	if (!LibFile.is_open())   //making sure the file is opened correctly
	{
		cout << "error opening Lib file, please recheck the name ";
		return;
	}

	while (!LibFile.eof())  //while we didnt reach the end of the file
	{
		string temp;
		LibFile >> temp;
		if (temp == "")  //if the file became empty(only have spaces or new lines
		{
			break;
		}


        //testing

        string newTemp; //handling the last digit in the gate type if it exists
        if (isdigit(temp[temp.size() - 1]))
            newTemp = temp.substr(0, temp.size() - 1);
        else
            newTemp=temp;
        //newtemp is the string without a number at the end

        //test if it is a logic circuit
       if(!((newTemp=="AND")||(newTemp=="OR") ||(newTemp=="NAND") ||(newTemp=="NOR") ||(newTemp=="XOR") ||(newTemp=="BUFFER") ||(newTemp=="NOT") ||(newTemp=="XNOR")))
        { cout<<"Wrong gate given in lib file";
            exit;
        }
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());  //we remove any commas
		FilesReading::Lib.addGateName(temp);  //we add the gat name to its vector
		LibFile >> temp;
		if (temp == "")  //if the file became empty(only have spaces or new lines
		{
			break;
		}

        //testing

        bool Digits1 = true;

        for (char c : temp) {
            if (!isdigit(c)) {
                Digits1 = false;
                break;
            }
        } //returns false when finding one counterexample(non digit)

        if (!Digits1) {
            cout<<"A proper digit is not entered in the input number for the gate in Lib file "<<endl;
            exit;
        }

		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());  //we remove any commas
		Lib.addInputNum(stoi(temp));  //we add the input size of the specified gate
		LibFile >> temp;
		if (temp == "")  //if the file became empty(only have spaces or new lines
		{
			break;
		}

        //testing

        for (int i = 0; i < temp.size() - 1; ++i) {
            if (!((temp[i] == '(') || (temp[i] == ')') || (temp[i] == '&') || (temp[i] == '~') ||
                  (temp[i] == '|'))) //check for spelling
            {
                if (temp[i] == 'i') { //i must follow it a number
                    i++;
                    if (!isdigit(temp[i])) {
                        cout << "Spelling error in logic expression in LIB file, or wrong format used." << endl;
                        exit;
                    }
                } else {
                    cout << "Spelling error in logic expression in LIB file, or wrong format used." << endl;
                    exit;
                }
            }
        }


            temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());  //we remove any commas
		Lib.addLogic(temp);  //we add the logic definition of the specified gate
		LibFile >> temp;
		if (temp == "")  //if the file became empty(only have spaces or new lines
		{
			break;
		}

            //testing

            bool Digits2 = true;

           for (char c : temp) {
               if (!isdigit(c)) {
                   Digits2 = false;
                   break;
               }
           }

           if (!Digits2) {
               cout<<"A proper digit is not entered in the input number for the gate "<<endl;
               exit;
           }

		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());   //we remove any commas
		Lib.addDelay(stoi(temp));

	}

	LibFile.close();
}

void FilesReading::ReadCirFile(string s)   //function to read contents from the cir file
{
	ifstream CirFile;
	CirFile.open(s);

	if (!CirFile.is_open())   //handling the case when the file name is wrong
	{
		cout << "error opening Cir file, please recheck the name ";
		return;
	}

	string temp;
	getline(CirFile, temp);
	//cout << temp << endl;
	CirFile >> temp;
	 
	while (temp != "COMPONENTS:")   //removing the unimportant line from the file
	{
		CirFile >> temp;
	//	cout << temp << endl;
		FilesReading::cir.addInput(temp[0]);  //adding the input variables
	}


	while (!CirFile.eof())    //while we are reading from the file and it didnt reach the end
	{

		LogicGate x;    //we create a logic gate and feed it its data from the cir file
		int inputCounter = 1;
		CirFile >> temp;
		//cout << temp << endl;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end()); //we remove any commas

		x.name = temp;
		cir.addComponentName(temp);    


		CirFile >> temp;
		//cout << temp << endl;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end()); //we remove any commas

		if ((temp[temp.size() - 1] <= 57) && (temp[temp.size() - 1] >= 48))
			inputCounter = (temp[temp.size() - 1]) - '0';




		x.type = temp;

		for (int i = 0; i < Lib.GatesNames.size(); i++)
		{
			if (Lib.GatesNames[i] == temp)
			{
				cir.logic.push_back(Lib.Logic[i]);
				x.logic = Lib.Logic[i];     //getting the logic and delay from the lib file struct
				x.delay = Lib.Delay[i];
				break;
			}
            else        //testing
            {
               cout<<"Gate type in cir file does not match the one in the lib file"<<endl;
                exit;
                }

		}



		cir.addType(temp);
		CirFile >> temp;
		//cout << temp << endl;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end()); //we remove any commas

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
		gates.push_back(x);   //we finally push the gate to its struct
	}


	CirFile.close();
}

void FilesReading::ReadStimFile(string s)  //function to read the contents of a stim file
{
	ifstream FileOpen;
	FileOpen.open(s);
	if (!FileOpen.is_open())  //handling an error instance
	{
		cout << "error opening stim file, please recheck the name ";
		return;
	}
	string temp;
	while (!FileOpen.eof())   //filling the appropriate vectors with the data needed
	{
		FileOpen >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
        //testing
         bool Digits3 = true;

        for (char c : temp) {
            if (!isdigit(c)) {
                Digits3 = false;
                break;
            }
        }

        if (Digits3) {
            cout<<"A proper digit is not entered in the input number for the gate "<<endl;
            exit;
        }
		stim.addDelay(stoi(temp));

		FileOpen >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
		stim.addInputVariable(temp);

		FileOpen >> temp;
		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());

       //testing

        if(!((temp=="1")||(temp=="0")))
        {
            cout<<"Input variables given wrong data in stim file";
            exit;

        }
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





	

	FileOpen.close();
}

void FilesReading::PrintLib()//function to print contents of the lib file
{
	Lib.PrintLib();
}


void FilesReading::PrintCir()//function to print contents of the cir file
{
	cir.PrintCir();
}

void FilesReading::PrintStim()  //function to print contents of the stim file
{
	stim.PrintSim();
}

void FilesReading::PrintGates()//function to print contents of the gates struct
{
	for (int i = 0; i < gates.size(); i++)
	{
		cout << gates[i].name << "  " << gates[i].type << "  " << gates[i].logic << "  " << gates[i].OutputName << "  ";
		for (int j = 0;j < gates[i].inputNames.size(); j++)
		{
			cout << gates[i].inputNames[j]<<"  ";
		}
		cout << "Output : " << gates[i].result<<"  "<< "Gate Delay : "<<gates[i].delay<<"  Time Stamp : "<<gates[i].timeStamp; //prints it in a semi tabular form
		cout << endl<<endl;
	}


}

