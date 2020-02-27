#include "Process.hpp"
#include "ProcessManager.hpp"
#include <list>
#include <iostream>
#include <fstream>


PCB::PCB(std::string processName, std::string filename)
{
	this->PID = 0;
	this->processName = processName;
	this->fileName = filename + ".txt";
	this->state = active;
}


int PCB::getPID()
{
	return PID;
}


void PCB::displayProcess()
{
	std::string sState;
	switch (state)
	{
		case 0:
			sState = "Active";
			break;
		case 1:
			sState = "Waiting";
			break;
		case 2:
			sState = "Ready";
			break;
		case 3:
			sState = "Terminated";
			break;
	}
	std::cout << "PID: " << PID << " | Nazwa pliku z programem: " << fileName << " | Nazwa procesu: " << processName << " | Stan: " << sState << "\n";
}


std::string PCB::getProcessName()
{
	return processName;
}


void PCB::setProcessState(processState newState)
{
	state = newState;
}


bool PCB::isProgramFileLoaded()
{
	std::ifstream input;
	input.open(fileName);

	if (input.good() == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}