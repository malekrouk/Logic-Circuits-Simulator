#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to read library (.lib) file
void readLibraryFile(const string& filename, string& componentName, int& numInputs, string& outputExpression, int& delayPs) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> componentName >> numInputs >> outputExpression >> delayPs;
        file.close();
    } else {
        cerr << "Unable to open library file" << endl;
    }
}

// Function to read circuit (.cir) file
void readCircuitFile(const string& filename, string& componentName, string& type, string& output, string& input1, string& input2) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        string section;
        while (getline(file, line)) {
            if (line == "COMPONENTS:") {
                section = line;
                continue;
            }
            if (section == "COMPONENTS:") {
                file >> componentName >> type >> output;
                if (type != "NOT") {
                    file >> input1 >> input2;
                } else {
                    file >> input1;
                }
                break; // Read only one line assuming one component per line
            }
        }
        file.close();
    } else {
        cerr << "Unable to open circuit file" << endl;
    }
}

// Function to read stimuli (.stim) file
void readStimuliFile(const string& filename, int& timeStamp, char& input, int& logicValue) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> timeStamp >> input >> logicValue;
        file.close();
    } else {
        cerr << "Unable to open stimuli file" << endl;
    }
}

int main() {
    // Variables to store data from files
    string componentName, outputExpression, type, output, input1, input2;
    int numInputs, delayPs, timeStamp, logicValue;

    // Read library file
    readLibraryFile("library_file.lib", componentName, numInputs, outputExpression, delayPs);

    // Read circuit file
    readCircuitFile("circuit_file.cir", componentName, type, output, input1, input2);

    // Read stimuli file
    readStimuliFile("stimuli_file.stim", timeStamp, input, logicValue);

    // Printing contents for verification
    cout << "Library component:" << endl;
    cout << componentName << ", " << numInputs << ", "
         << outputExpression << ", " << delayPs << endl;

    cout << "Circuit component:" << endl;
    cout << componentName << ", " << type << ", " << output << ", " << input1 << ", " << input2 << endl;

    cout << "Stimuli:" << endl;
    cout << timeStamp << ", " << input << ", " << logicValue << endl;

    return 0;
}
