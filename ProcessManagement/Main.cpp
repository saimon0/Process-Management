#include <iostream>
#include <string>
#include "Shell.hpp"
#include "Process.hpp"
#include "ProcessManager.hpp"


PCB* runningProcess;
ProcessManager* processManager;

int main()
{
	std::cout << "Modul zarzadzania procesami wzorowany na systemie Linux\n";

	Shell shell;
	std::string komenda;
	
	while (shell.on_off) //petla glowna systemu
	{
		std::getline(std::cin, komenda);
		shell.wybierz_metode(komenda);
	}
	return 0;
}