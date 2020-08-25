#include "Functions.hpp"
#include <iostream>
#include <thread>
#pragma warning (disable : 6385)

void ManageProcess(CProcess process)
{
	if (!process.hProcess)
		return;
	int nViolations = 0; //Reserved.

	std::cout << "[Log] Started monitoring process: " << process.dwProcessId << std::endl;

	while (1)
	{
		//If the process is using more than 15% CPU
		if (GetCpuUsage(process.hProcess) > 15)
		{
			NtSuspendProcess(process.hProcess);
			std::cout << "[Log] Suspended process: " << process.dwProcessId << std::endl;

			std::this_thread::sleep_for(std::chrono::seconds(30)); //Timeout option will be added

			NtResumeProcess(process.hProcess);
			std::cout << "[Log] Resumed process: " << process.dwProcessId << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main()
{
	SetConsoleTitleA("UsageBeGone");

	ParseNames();
	StoreProcesses(vProcesses, vNames);

	std::thread* tThreads = new std::thread[vProcesses.size()];

	for (size_t pos = 0; pos < vProcesses.size(); pos++)
		tThreads[pos] = std::thread(ManageProcess, vProcesses[pos]);

	for (size_t pos = 0; pos < vProcesses.size(); pos++)
		tThreads[pos].join();

	//TODO: Figure out how to call Cleanup after the user clicks "X" (CtrlHandler?)

	std::cout << "[Log] Exiting..." << std::endl;

	return 0;
}