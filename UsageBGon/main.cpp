#include "Functions.hpp"
#include "Parser.hpp"
#include <thread>

//Víc zase zítra ve?er
//Díky za sledování :)

#pragma warning (disable : 6385)

void CreateThreads()
{
	std::thread* tThreads = new std::thread[Parser::vProcesses.size()];

	for (size_t pos = 0; pos < Parser::vProcesses.size(); pos++)
		tThreads[pos] = std::thread(Funcs::ManageProcess, Parser::vProcesses[pos]);

	for (size_t pos = 0; pos < Parser::vProcesses.size(); pos++)
		tThreads[pos].join();
}

int main()
{
	SetConsoleTitleA("UsageBeGone");

	if (Parser::ReadSettings())
	{
		std::cout << "[Log] Settings loaded succesfully!" << std::endl;
		std::cout << "[Settings] CPULimit = " << Parser::Settings::nCPULimit << std::endl;
		std::cout << "[Settings] Timeout = " << Parser::Settings::nTimeout << std::endl;
		std::cout << std::endl;
	}
	else
		std::cout << "[Error] Couldn't load settings!" << std::endl;

	if (Parser::ReadProcessNames()) 
	{
		std::cout << "[Log] Process Names loaded succesfully!" << std::endl;
		if (Parser::vNames.empty())
			std::cout << "[Warn] Process Names are empty! No applications will be monitored!" << std::endl;
	}

	else
		std::cout << "[Error] Couldn't load process names!" << std::endl;

	Funcs::StoreProcesses(Parser::vProcesses, Parser::vNames);
	
	CreateThreads();

	std::cout << "Program halted. Press any key to exit." << std::endl;

	std::cin.get();

	return 0;
}