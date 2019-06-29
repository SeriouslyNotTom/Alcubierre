#include <alcubierre/forensics/Logging.h>

#ifdef _WIN32
#include <Windows.h>
#include <debugapi.h>
#endif
#include <iostream>
#include <string>


	void Logger::General(char* msg)
	{
		LogFunc("[General] ", msg);
	}

	void Logger::LogFunc(char* Header, char* msg)
	{
		char* output = new char[strlen(Header) + strlen(msg)];
		strcpy(output, Header);
		strcat(output, msg);
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