#pragma once
#include <Windows.h>

void __stdcall NtSuspendProcess(HANDLE hProcess); //For suspending processes (undocumented ntdll function)

void __stdcall NtResumeProcess(HANDLE hProcess);  //For resuming processes (undocumented ntdll function)