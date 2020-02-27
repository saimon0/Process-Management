#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <regex>
#include <fstream>
#include <vector>
#include <string>


enum processState
{ 
	active = 0, waiting = 1, ready = 2, terminated = 3
};


class PCB
{
public:
	int PID;
	processState state;
	std::string processName;
	std::string fileName;

	PCB(std::string processName, std::string fileName);
	PCB() {};
	PCB* parent;
	std::list<PCB*> children;
	int getPID();
	void displayProcess();
	std::string getProcessName();
	void setProcessState(processState newState);
	bool isProgramFileLoaded();
};