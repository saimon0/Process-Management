#include <iostream>
#include <string>
#include <list>
#include "ProcessManager.hpp"
#include "Process.hpp"

extern PCB* runningProcess;

int pidCounter = 1;

ProcessManager::ProcessManager()
{
	createInitProcess();
}


void ProcessManager::createInitProcess()
{
	PCB* newProcess = new PCB("init","init");
	newProcess->PID = pidCounter;
	newProcess->parent = nullptr;
	allProcesses.push_back(newProcess);
	runningProcess = newProcess;
}


void ProcessManager::createProcess(std::string processName, std::string fileName)
{
	PCB *newProcess = new PCB(processName, fileName);
	bool fileState = newProcess->isProgramFileLoaded();
	if (fileState == true)
	{
		if (allProcesses.size() == 1)
		{
			PCB* currentRunningProcess = runningProcess;
			newProcess->PID = ++pidCounter;
			newProcess->parent = findProcessByPID(1);
			newProcess->parent->children.push_back(newProcess);
			currentRunningProcess->state = ready;
			newProcess->state = active;
			allProcesses.push_back(newProcess);
			runningProcess = newProcess;
		}
		else if (allProcesses.size() > 1)
		{
			newProcess->state = ready;
			PCB* currentRunningProcess = runningProcess;
			currentRunningProcess->state = ready;
			newProcess->PID = ++pidCounter;
			newProcess->parent = findProcessByPID(1);
			newProcess->parent->children.push_back(newProcess);
			newProcess->state = ready;
			findProcessByName("init")->state = active;
			allProcesses.push_back(newProcess);
			runningProcess = findProcessByName("init");
		}
	}
	else
	{
		std::cout << "Nie znaleziono wskazanego pliku programu\n";
	}
}


void ProcessManager::displayAllProcesses()
{
	if (allProcesses.empty() == true)
	{
		std::cout << "Lista jest pusta\n";
	}
	else
	{
	for (auto it = allProcesses.begin(); it != allProcesses.end(); it++)
		{
			(*it)->displayProcess();
		}
	}
}


void ProcessManager::displayReadyProcesses()
{
	std::list<PCB*> readyProcesses;

	for (auto it = allProcesses.begin(); it != allProcesses.end(); it++)
	{
		if ((*it)->state == ready)
		{
			readyProcesses.push_back(*it);
		}
	}

	if (readyProcesses.empty() == true)
	{
		std::cout << "Lista procesow gotowych jest pusta\n";
	}
	else
	{
		for (auto it = readyProcesses.begin(); it != readyProcesses.end(); it++)
		{
			(*it)->displayProcess();
		}
	}
}


void ProcessManager::displayWaitingProcesses()
{
	std::list<PCB*> waitingProcesses;
	for (auto it = allProcesses.begin(); it != allProcesses.end(); it++)
	{
		if ((*it)->state == waiting)
		{
			waitingProcesses.push_back(*it);
		}
	}

	if (waitingProcesses.empty() == true)
	{
		std::cout << "Lista procesow oczekujacych jest pusta\n";
	}
	else
	{
		for (auto it = waitingProcesses.begin(); it != waitingProcesses.end(); it++)
		{
			(*it)->displayProcess();
		}
	}
}


void ProcessManager::removeProcess(std::string processName)
{
	if (processName == "init")
	{
		std::cout << "Nie mozna usunac procesu 'init'\n";
	}
	else if (ifProcessExists(processName) == false)
	{
		std::cout << "Nie znaleziono wskazanego procesu\n";
	}
	else
	{
		PCB* process = findProcessByName(processName);
		
		if (process == runningProcess)
		{
			findProcessByName("init")->state = active;
			runningProcess = findProcessByName("init");
		}
		if (process->state == waiting)
		{
			std::cout << "Nie mozna usunac procesu ze statusem 'waiting'\n";
		}
		else if (process->children.empty() == true)
		{
			process->parent->children.remove(process);
			allProcesses.remove(process);
			delete process;
		}
		else if (process->children.empty() == false)
		{
			std::list<PCB*> children = process->children;
			for (auto it = children.begin(); it != children.end(); it++)
			{
				(*it)->parent = process->parent;
				(*it)->parent->children.push_back(*it);
				(*it)->children.remove(*it);
			}
			process->parent->children.remove(process);
			allProcesses.remove(process);
			delete process, children;
		}
	}
}


PCB* ProcessManager::findProcessByName(std::string processName)
{
	for (auto it : allProcesses)
	{
		if (it->getProcessName() == processName)
		{
			return it;
			break;
		}
	}
}


PCB* ProcessManager::findProcessByPID(unsigned int PID)
{
	for (auto it : allProcesses)
	{
		if (it->getPID() == PID)
		{
			return it;
			break;
		}
	}
}


bool ProcessManager::ifProcessExists(std::string processName)
{
	for (auto it = allProcesses.begin(); it != allProcesses.end(); it++)
	{
		if ((*it)->getProcessName() == processName)
		{
			return true;
			break;
		}
	}
	return false;
}


void ProcessManager::createSonProcess(std::string parentProcessName, std::string childProcessName, std::string fileName)
{
	if (ifProcessExists(parentProcessName) == true)
	{
		PCB* parentProcess = findProcessByName(parentProcessName);
		if (parentProcess->state == terminated)
		{
			std::cout << "Nie mozna utworzyc procesu-potomka dla procesu w stanie 'terminated'\n";
		}
		else
		{
			PCB *childProcess = new PCB(childProcessName, fileName);
			bool fileState = childProcess->isProgramFileLoaded();
			if (fileState == true)
			{
				if (allProcesses.size() == 1)
				{
					PCB* currentRunningProcess = runningProcess;
					childProcess->PID = ++pidCounter;
					childProcess->parent = findProcessByName("init");
					childProcess->parent->children.push_back(childProcess);
					currentRunningProcess->state = ready;
					childProcess->state = active;
					allProcesses.push_back(childProcess);
					runningProcess = childProcess;
				}
				else if (allProcesses.size() > 1)
				{
					childProcess->state = ready;
					PCB* currentRunningProcess = runningProcess;
					currentRunningProcess->state = ready;
					childProcess->PID = ++pidCounter;
					childProcess->parent = parentProcess;
					childProcess->parent->children.push_back(childProcess);
					childProcess->state = ready;
					findProcessByName("init")->state = active;
					allProcesses.push_back(childProcess);
					runningProcess = findProcessByName("init");
				}
			}
			else
			{
				std::cout << "Nie znaleziono wskazanego pliku programu\n";
			}
		}
	}
	else
	{
		std::cout << "Wskazany proces rodzica nie istnieje\n";
	}
}


void ProcessManager::displayProcessChildren(std::string procesName)
{
	if (ifProcessExists(procesName) == true)
	{
		if (findProcessByName(procesName)->children.size() == 0)
		{
			std::cout << "Wskazany proces nie posiada dzieci\n";
		}
		else
		{
			for (auto child : findProcessByName(procesName)->children)
			{
				child->displayProcess();
			}
		}
	}
	else
	{
		std::cout << "Wskazany proces nie istnieje\n";
	}
}


void ProcessManager::setProcessState(std::string processName, std::string State)
{
	if (ifProcessExists(processName) == true)
	{
		PCB* process = findProcessByName(processName);
		processState currentState = process->state;

		if (currentState == terminated)
		{
			std::cout << "Nie mozna zmienic stanu procesu ze stanem 'terminated'\n";
		}
		else if (processName == "init" && State == "terminated")
		{
			std::cout << "Nie mozna zmienic stanu procesu 'init' na 'terminated'\n";
		}
		else if (State == "active")
		{
			if (currentState == active)
			{
				std::cout << "Wskazany proces ma juz stan 'active'\n";
			}
			else if (currentState == ready)
			{
				PCB* currentRunningProcess = runningProcess;
				currentRunningProcess->state = ready;
				process->state = active;
				runningProcess = process;
			}
			else
			{
				std::cout << "Tylko procesy ze stanem 'ready' moga przejsc do stanu 'active'\n";
			}
		}
		else if (State == "ready")
		{
			if (currentState == ready)
			{
				std::cout << "Wskazany proces ma juz stan 'ready'\n";
			}
			else if (currentState == waiting)
			{
				process->state = ready;
			}
			else if (currentState == active)
			{
				process->state = ready;
				findProcessByName("init")->state = active;
				runningProcess = findProcessByName("init");
			}
		}
		else if (State == "waiting")
		{
			if (currentState == waiting)
			{
				std::cout << "Wskazany proces ma juz stan 'waiting'\n";
			}
			else if (currentState != active)
			{
				std::cout << "Tylko procesy ze stanem 'active' moga zmienic stan na 'waiting'\n";
			}
			else
			{
				process->state = waiting;
				findProcessByName("init")->state = active;
				runningProcess = findProcessByName("init");
			}
		}
		else if (State == "terminated")
		{
			if (currentState == terminated)
			{
				std::cout << "Wskazany proces ma juz stan 'terminated'\n";
			}
			else if (currentState != active)
			{
				std::cout << "Tylko procesy ze stanem 'active' moga zmienic stan na 'terminated'\n";
			}
			else
			{
				process->state = terminated;
				findProcessByName("init")->state = active;
				runningProcess = findProcessByName("init");
			}
		}
		else
		{
			std::cout << "Nie znaleziono wskazanego stanu procesu\n";
		}
	}
	else
	{
		std::cout << "Wskazany proces nie istnieje\n";
	}
}