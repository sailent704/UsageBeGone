#include "NTAPI.hpp"

//Generic prototype for NtSuspendProcess and NtResumeProcess
using tProcess = void(__stdcall*)(HANDLE hProc);

void __stdcall NtSuspendProcess(HANDLE hProcess)
{
	//Get function pointer
	static tProcess ntSuspendProcess = reinterpret_cast<tProcess>(GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtSuspendProcess"));

	//Call the original
	return ntSuspendProcess(hProcess);
}

void __stdcall NtResumeProcess(HANDLE hProcess)
{
	//Get function pointer
	static tProcess ntResumeProcess = reinterpret_cast<tProcess>(GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtResumeProcess"));

	//Call the original
	return ntResumeProcess(hProcess);
}
