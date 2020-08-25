#pragma once
#include "Functions.hpp"
#undef CreateFile

namespace Parser
{
	inline std::vector<CProcess> vProcesses;
	inline std::vector<std::wstring> vNames;
	
	bool FileExists(const char* lpName);
	bool CreateFile(const char* lpName, const char* lpContents = "");

	void ResetSettings(); //Writes a base settings file
	bool ReadSettings(); //Reads Settings
	bool ReadProcessNames(); //Reads Process Names

	namespace Settings
	{
		inline int nTimeout = 30;
		inline int nCPULimit = 15;
	}
}
