#pragma once
#include "NTAPI.hpp"
#include <vector>
#include <string>
#include <fstream>

class CProcess
{
public:
	HANDLE hProcess = nullptr;
	DWORD dwProcessId = 0;

	CProcess(HANDLE hProc, DWORD dwProcId)
		: hProcess(hProc), dwProcessId(dwProcId)
	{}
};

inline std::vector<CProcess> vProcesses;
inline std::vector<std::wstring> vNames;

void StoreProcesses(std::vector<CProcess>& vProc, const std::vector<std::wstring>& vNames);

void Cleanup(std::vector<CProcess>& vProc);

int GetCpuUsage(HANDLE hProcess, DWORD dwMeasureTime = 1000);

void ParseNames(); //Move me to some parser namespace