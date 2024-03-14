#pragma once
#include<fstream>
#include<vector>
#include<string>
#include"Structs.h"
using namespace std;
class FilesReading
{
public:
	LibStruct Lib;
	CircuitStruct cir;
	StimStruct stim;
	void ReadLibFile(string s);
	void ReadCirFile(string s);
	void ReadStimFile(string s);

};

