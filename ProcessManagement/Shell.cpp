#include <iostream>
#include <vector>
#include <string>
#include "Shell.hpp"
#include "ProcessManager.hpp"
#include "Process.hpp"
#include <iterator>
#include <sstream>
#include <fstream>

using namespace std;

extern ProcessManager* processManager;

Shell::Shell()
{
	on_off = true;
	processManager = new ProcessManager();
}


bool numer(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it))
	{
		++it;
	}
	return !s.empty() && it == s.end();
}


void Shell::CP(std::string nazwa_procesu, std::string nazwa_pliku)
{
	processManager->createProcess(nazwa_procesu, nazwa_pliku);
}


void Shell::CSP(std::string nazwa_procesu_rodzica, std::string nazwa_procesu_dziecka, std::string nazwa_pliku)
{
	processManager->createSonProcess(nazwa_procesu_rodzica, nazwa_procesu_dziecka, nazwa_pliku);
}


void Shell::DP(std::string nazwa_procesu)
{
	processManager->removeProcess(nazwa_procesu);
}


void Shell::SP(std::string nazwa_procesu)
{
	if (processManager->ifProcessExists(nazwa_procesu) == true)
	{
		PCB* process = processManager->findProcessByName(nazwa_procesu);
		process->displayProcess();
	}
	else
	{
		std::cout << "Nie znaleziono procesu o wskazanej nazwie\n";
	}
}


void Shell::DAP()
{
	processManager->displayAllProcesses();
}


void Shell::DWP()
{
	processManager->displayWaitingProcesses();
}


void Shell::DRP()
{
	processManager->displayReadyProcesses();
}


void Shell::SPS(std::string nazwa_procesu, std::string stan)
{
	processManager->setProcessState(nazwa_procesu, stan);
}


void Shell::DPC(std::string nazwa_procesu)
{
	processManager->displayProcessChildren(nazwa_procesu);
}


void Shell::EXIT()
{
	on_off = false;
}


void Shell::HELP()
{
	string line;

	ifstream plik("help.txt");
	if (plik.is_open())
	{
		while (getline(plik, line))
		{
			cout << line << endl;
		}
		plik.close();
	}
	else
	{
		cout << "Nie mozna otworzyc pliku\n" << endl;
	}
}





void Shell::wybierz_metode(std::string komenda)
{
	istringstream pom(komenda);
	vector<std::string> polecenie;
	do
	{
		string slowo;
		pom >> slowo;
		polecenie.push_back(slowo);
	} while (pom);
	if (polecenie[0] == "CP")
	{
		if (polecenie.size() != 4)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			CP(polecenie[1], polecenie[2]);
		}
	}
	else if (polecenie[0] == "CSP")
	{
		if (polecenie.size() != 5)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			CSP(polecenie[1], polecenie[2], polecenie[3]);
		}
	}
	else if (polecenie[0] == "DP")
	{
		if (polecenie.size() != 3)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			DP(polecenie[1]);
		}
	}
	else if (polecenie[0] == "SP")
	{
		if (polecenie.size() != 3)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			SP(polecenie[1]);
		}
	}
	else if (polecenie[0] == "DAP")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			DAP();
		}
	}
	else if (polecenie[0] == "DWP")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			DWP();
		}
	}
	else if (polecenie[0] == "DRP")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			DRP();
		}
	}
	else if (polecenie[0] == "SPS")
	{
	if (polecenie.size() != 4)
	{
		cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
	}
	else
	{
		SPS(polecenie[1], polecenie[2]);
	}
	}
	else if (polecenie[0] == "DPC")
	{
		if (polecenie.size() != 3)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			DPC(polecenie[1]);
		}
	}
	else if (polecenie[0] == "EXIT")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			EXIT();
		}
	}
	else if (polecenie[0] == "HELP")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			HELP();
		}
	}
	else
	{
		cout << "Nieprawidlowe polecenie" << endl;
	}
}