#include "Functions.hpp"
#include <TlHelp32.h>
#include <iostream>
#include <sstream>
#include <thread>

void StoreProcesses(std::vector<CProcess>& vProc, const std::vector<std::wstring>& vNames)
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
}

void Cleanup(std::vector<CProcess>& vProc)
{
	for (auto& proc : vProc) {
		NtResumeProcess(proc.hProcess);
		CloseHandle(proc.hProcess);
	}
}

int GetCpuUsage(HANDLE hProcess, DWORD dwMeasureTime)
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

	return (i64KernelTime + i64UserTime) / (dwMeasureTime * 1000U); //Milliseconds to Microseconds
}

void ParseNames()
{
	std::wifstream in("names.txt"); //Open the file
	std::wstringstream stream;

	stream << in.rdbuf(); //Read the whole file

	in.close();

	std::wstring sComplete = stream.str();

	size_t pos = 0;
	std::wstring sBuffer;

	while (pos <= sComplete.length())
	{
		if (pos == sComplete.length())
		{
			vNames.push_back(sBuffer);
			break;
		}

		if (sComplete[pos] == '\n') {
			std::wcout << "buf: " << sBuffer << std::endl;

			vNames.push_back(sBuffer);
			sBuffer.clear();

			pos++;
			continue;
		}

		sBuffer.push_back(sComplete[pos]);
		pos++;
	}
}
