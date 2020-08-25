#pragma once
#include "NTAPI.hpp"
#include <vector>
#include <string>
#include <iostream>

class CProcess
{
public:
	HANDLE hProcess = nullptr;
	DWORD dwProcessId = 0;

	CProcess(HANDLE hProc, DWORD dwProcId)
		: hProcess(hProc), dwProcessId(dwProcId)
	{}
};

namespace Funcs
{
	void StoreProcesses(std::vector<CProcess>& vProc, const std::vector<std::wstring>& vNames);

	void Cleanup(std::vector<CProcess>& vProc);

	int GetCpuUsage(HANDLE hProcess, unsigned long long dwMeasureTime = 1000);

	void ManageProcess(CProcess hProcess);
}
