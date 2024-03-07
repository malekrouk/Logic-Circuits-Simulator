#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to read library file
void readLibraryFile(const string& filename, string& componentName, int& numInputs, string& outputExpression, int& delayPs) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> componentName >> numInputs >> outputExpression >> delayPs;
        file.close();
    }
    else {
        cerr << "Unable to open library file: " << filename << endl;
    }
}

// Function to read circuit file
void readCircuitFile(const string& filename, string& inputs, string& components) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        string section;
        while (getline(file, line)) {
            if (line == "INPUTS:") {
                section = line;
                continue;
            }
            if (line == "COMPONENTS:") {
                section = line;
                continue;
            }
            if (section == "INPUTS:") {
                inputs += line + "\n";
            }
            if (section == "COMPONENTS:") {
                components += line + "\n";
            }
        }
        file.close();
    }
    else {
        cerr << "Unable to open circuit file: " << filename << endl;
    }
}

// Function to read stimuli file
void readStimuliFile(const string& filename, int& timeStamp, char& input, int& logicValue) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> timeStamp >> input >> logicValue;
        file.close();
    }
    else {
        cerr << "Unable to open stimuli file: " << filename << endl;
    }
}

int main() {
    // Test circuit files
    string circuitFiles[] = { "C1", "C2", "C3" };

    for (const auto& circuit : circuitFiles) {
        string libFile = circuit + ".lib";
        string cirFile = circuit + ".cir";
        string stimFile = circuit + ".stim";

        // Variables to store data from files
        string componentName, outputExpression, inputs, components;
        int numInputs, delayPs, timeStamp, logicValue;
        char input;

        // Read library file
        readLibraryFile(libFile, componentName, numInputs, outputExpression, delayPs);

        // Read circuit file
        readCircuitFile(cirFile, inputs, components);

        // Read stimuli file
        readStimuliFile(stimFile, timeStamp, input, logicValue);

        // Print contents for verification
        cout << "Test Circuit: " << circuit << endl;
        cout << "Library component:" << endl;
        cout << componentName << ", " << numInputs << ", "
            << outputExpression << ", " << delayPs << endl;

        cout << "Circuit inputs:" << endl;
        cout << inputs;

        cout << "Circuit components:" << endl;
        cout << components;

        cout << "Stimuli:" << endl;
        cout << timeStamp << ", " << input << ", " << logicValue << endl;
        cout << endl;
    }

    return 0;
}
