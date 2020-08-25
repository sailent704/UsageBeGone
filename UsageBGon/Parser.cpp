#include "Parser.hpp"
#include <string>
#include <sstream>
#include <fstream>

#pragma warning (disable : 4244) //fuck off warnings

size_t FindCommentEnd(size_t begin, const std::wstring& string)
{
	if (string[begin] != ';')
		return -1; //Error - begin is not the beginning of a comment!

	size_t pos = begin;
	while (string[pos] != '\n' && pos != string.length())
		pos++;

	return pos + 1;
}

bool Parser::CreateFile(const char* lpName, const char* lpContents)
{
	if (FileExists(lpName))
		return false; //File couldn't be created

	std::ofstream f(lpName);
	f << lpContents;
	f.close();

	return true;
}

bool Parser::FileExists(const char* lpName)
{
	std::ifstream f(lpName);

	bool bGood = f.good();
	if (bGood)
		f.close();

	return bGood;
}

void Parser::ResetSettings()
{
	std::ofstream settings("settings.conf");

	if (FileExists("settings.conf"))
		settings.clear();

	settings << "; Timeout represents how long a process should stay suspended in seconds. (Default: 30)\n";
	settings << "I:Timeout=30\n";
	settings << "; CPULimit represents the maximum CPU usage for a given process in percent. (Default: 15)\n";
	settings << "I:CPULimit=15";

	settings.close();
}

bool Parser::ReadSettings()
{
	if (!FileExists("settings.conf")) {
		ResetSettings();
		return false; //Couldn't read settings
	}
		
	std::wifstream settings("settings.conf");

	std::wstring sCompleteFile;
	std::wstringstream stream;
	stream << settings.rdbuf();

	sCompleteFile = stream.str(); //Read the complete file and write it into the sCompleteFile string

	//Loop through the whole file and read the settings
	
	for (size_t pos = 0; pos <= sCompleteFile.length(); pos++)
	{
		/*{
			size_t nPotentialEnd = FindCommentEnd(pos, sCompleteFile);

			if (nPotentialEnd != static_cast<size_t>(nPotentialEnd))
				pos = nPotentialEnd;
		}*/

		//Now check the type
		if (sCompleteFile[pos] == 'I' || sCompleteFile[pos] == 'B') //If the current character is a B or I
		{
			//Check if the next character is a ':' (because 'B' or 'I' can be a setting name)
			if (sCompleteFile[pos + 1] == ':')
			{
				pos += 2;
				std::string sValueName;

				while (sCompleteFile[pos] != '=') {
					sValueName.push_back(sCompleteFile[pos]); //Push back the value name
					pos++;
				}
				
				pos++;

				//Read the value
				std::string sValue;

				while (sCompleteFile[pos] != '\n' && pos != sCompleteFile.length())
				{
					sValue.push_back(sCompleteFile[pos]);
					pos++;
				}
				
				if (sValueName == "Timeout")
					Settings::nTimeout = std::stoi(sValue);

				else if (sValueName == "CPULimit")
					Settings::nCPULimit = std::stoi(sValue);
			}
		}
	}

	settings.close(); //Don't leave file handles open :(

	return true;
}

bool Parser::ReadProcessNames()
{
	if (!FileExists("processes.conf")) {
		CreateFile("processes.conf", "; The application only monitors the processes listed here!\n");
		return false;
	}
	
	//This is gonna be simple
	std::wifstream processes("processes.conf");

	std::wstring sCompleteFile;
	std::wstringstream stream; //These really make stuff easy
	stream << processes.rdbuf();
	sCompleteFile = stream.str();

	for (size_t pos = 0; pos <= sCompleteFile.length(); pos++)
	{
		std::wstring sBuffer;

		if (sCompleteFile[pos] == ';')
		{
			size_t nPotentialEnd = FindCommentEnd(pos, sCompleteFile);

			if (nPotentialEnd != static_cast<size_t>(-1)) //I'm retarded
				pos = nPotentialEnd;
		}

		while (sCompleteFile[pos] != '\n' && pos != sCompleteFile.length()) 
		{
			sBuffer.push_back(sCompleteFile[pos]);
			pos++;
		}
		
		if (!sBuffer.empty())
			vNames.push_back(sBuffer);
	}

	processes.close();

	return true; 
}
