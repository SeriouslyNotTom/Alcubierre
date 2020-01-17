#pragma once
#define GLFW_INCLUDE_NONE
#include <iostream>
#include <Alcubierre/Tests/TestProgram_handler.h>
#include <Alcubierre/Libraries/Debug/Metrics.h>
#include <Alcubierre/Libraries/Render/Window/WindowManager.h>
#include <Alcubierre/StateManager.h>
#include <Alcubierre/Engine.h>
#include <Alcubierre/build_info.h>

struct _Info
{
	const char* Alcubierre_Build_Type;
	const char* Alcubierre_Build_Date;
};

class _Basic_Config
{
	bool windowed = true;
};

namespace Alcubierre
{
	static _Info Info;
	static _Basic_Config Basic_Config;
	extern int argc;
	extern char* argv;
	void Accept_Arguments(int argc, char* argv);
	void Initialize_Core();
	void Exit(int code);
}