#pragma once
#include <vector>
#include <string>
#include <iostream>


class Shell
{
public:
	bool on_off;
	Shell();
	void wybierz_metode(std::string komenda);

	void CP(std::string nazwa_procesu, std::string nazwa_pliku);
	void CSP(std::string nazwa_procesu_rodzica, std::string nazwa_procesu_dziecka, std::string nazwa_pliku);
	void DP(std::string nazwa_procesu);
	void SP(std::string nazwa_procesu);

	void DAP();
	void DWP();
	void DRP();
	void SPS(std::string processName, std::string stan);
	void DPC(std::string nazwa_procesu);

	void EXIT(); 
	void HELP();
};