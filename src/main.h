// CMakeProject2.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <Alcubierre/Tests/TestProgram_handler.h>
#include <Alcubierre/Libraries/Debug/Metrics.h>

class Alcubierre
{
public:
	static TestProgram_handler Test_Programs;
	static Debug_Metrics DebugMetrics;
};
