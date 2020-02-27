#pragma once
#include <iostream>
#include <list>
#include <string>
#include "Process.hpp"


class ProcessManager
{
public:
	std::list<PCB*> allProcesses;
	ProcessManager();

	void createProcess(std::string processName, std::string fileName);
	void createSonProcess(std::string parentProcessName, std::string childProcessName, std::string fileName);
	void createInitProcess();

	void displayAllProcesses();
	void displayReadyProcesses();
	void displayWaitingProcesses();
	void displayProcessChildren(std::string procesName);

	void setProcessState(std::string processName, std::string state);
	void removeProcess(std::string processName);
	bool ifProcessExists(std::string processName);
	PCB* findProcessByName(std::string processName);
	PCB* findProcessByPID(unsigned int PID);
};
