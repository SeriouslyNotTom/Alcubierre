#include <alcubierre/forensics/Logging.h>

#ifdef _WIN32
#include <Windows.h>
#include <debugapi.h>
#endif
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string>


	void Logger::General(std::string msg)
	{
		LogFunc("[General] ", msg);
	}

	void Logger::Raw(char* msg)
	{
		LogFunc("", msg);
	}

	void Logger::LogFunc(char* Header, std::string msg)
	{
		char* output = new char[strlen(Header) + strlen(msg.c_str())];
		strcpy(output, Header);
		strcat(output, msg.c_str());
		strcat(output, "\n");

#ifdef _WIN32
		LPWSTR message;
		wchar_t* wString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, output, -1, wString, 4096);
		message = wString;
		OutputDebugStringW(message);
#endif
		fprintf(stdout, output);
	}