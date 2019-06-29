#pragma once

class Logger
{
public:
	static void General(char* msg);
private:
	static void LogFunc(char* Header, char* msg);
};