#include "Parser.hpp"
#include <TlHelp32.h>
#include <thread>

void Funcs::StoreProcesses(std::vector<CProcess>& vProc, const std::vector<std::wstring>& vNames)
{
	//Loop over processes
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32W mEntry = { sizeof(PROCESSENTRY32W) };
	
	Process32FirstW(hSnap, &mEntry);
	do
	{
		//Check if name matches
		for (auto& name : vNames) 
		{
			if (!_wcsicmp(name.c_str(), mEntry.szExeFile))
			{
				HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS /*change me*/, FALSE, mEntry.th32ProcessID);
				if (!hProc)
					std::wcout << "[Error] Failed to open process " << mEntry.szExeFile << " - Error 0x" << GetLastError() << std::endl;

				else {
					CProcess curProcess(hProc, mEntry.th32ProcessID);
					vProc.push_back(curProcess);
				}
			}
		}
	} while (Process32NextW(hSnap, &mEntry));

	CloseHandle(hSnap); //Memory leak :flushed:
}

void Funcs::Cleanup(std::vector<CProcess>& vProc)
{
	for (auto& proc : vProc) {
		NtResumeProcess(proc.hProcess);
		CloseHandle(proc.hProcess);
	}
}

int Funcs::GetCpuUsage(HANDLE hProcess, unsigned long long dwMeasureTime)
{
	FILETIME ftKernel1, ftUser1;
	FILETIME ftKernel2, ftUser2;

	{
		FILETIME ftDummy1, ftDummy2;

		GetProcessTimes(hProcess, &ftDummy1, &ftDummy2, &ftKernel1, &ftUser1);

		std::this_thread::sleep_for(std::chrono::milliseconds(dwMeasureTime));

		GetProcessTimes(hProcess, &ftDummy1, &ftDummy2, &ftKernel2, &ftUser2);
	}
	int64_t i64KernelTime, i64UserTime;
	{
		ULARGE_INTEGER i64Kernel1 = { ftKernel1.dwLowDateTime, ftKernel1.dwHighDateTime };
		ULARGE_INTEGER i64Kernel2 = { ftKernel2.dwLowDateTime, ftKernel2.dwHighDateTime };

		i64KernelTime = i64Kernel2.QuadPart - i64Kernel1.QuadPart;

		ULARGE_INTEGER i64User1 = { ftUser1.dwLowDateTime, ftUser1.dwHighDateTime };
		ULARGE_INTEGER i64User2 = { ftUser2.dwLowDateTime, ftUser2.dwHighDateTime };

		i64UserTime = i64User2.QuadPart - i64User1.QuadPart;
	}

	return static_cast<int>((i64KernelTime + i64UserTime) / (dwMeasureTime * 1000U)); //Milliseconds to Microseconds
}

void Funcs::ManageProcess(CProcess hProcess)
{
	if (!hProcess.hProcess)
		return;
	int nViolations = 0; //Reserved.

	std::cout << "[Log] Started monitoring process: " << hProcess.dwProcessId << std::endl;

	while (1)
	{
		//If the process is using more than nCPULimit% CPU
		if (Funcs::GetCpuUsage(hProcess.hProcess) > Parser::Settings::nCPULimit)
		{
			NtSuspendProcess(hProcess.hProcess);
			std::cout << "[Log] Suspended process: " << hProcess.dwProcessId << std::endl;

			std::this_thread::sleep_for(std::chrono::seconds(Parser::Settings::nTimeout)); //Timeout option will be added

			NtResumeProcess(hProcess.hProcess);
			std::cout << "[Log] Resumed process: " << hProcess.dwProcessId << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

	