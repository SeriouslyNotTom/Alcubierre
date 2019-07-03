#pragma once

#include <stdlib.h>
#include <string>

class Logger
{
public:
	static void General(std::string msg);
	static void Raw(char* msg);
private:
	static void LogFunc(char* Header, std::string msg);
};