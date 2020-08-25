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

	Parser::ReadSettings();
	Parser::ReadProcessNames();

	Funcs::StoreProcesses(Parser::vProcesses, Parser::vNames);
	
	CreateThreads();

	Sleep(3000);
	return 0;
}