#pragma once
#define GLFW_INCLUDE_NONE
#include <iostream>
#include <Alcubierre/Engine/Engine.h>
#include <Alcubierre/build_info.h>
#include <map>
#include <stdlib.h>
#include <vector>
#include <memory>
#include <functional>

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
	extern bool Debug_Mode;
	static _Info Info;
	static _Basic_Config Basic_Config;
	extern int argc;
	extern char* argv;
	extern std::vector<std::function<void()>> hook_list;
	extern std::function<void()>** ban_list;
	void Accept_Arguments(int argc, char* argv);
	void Initialize_Core();
	bool addHook(std::function<void()> func);
	void Exit(int code);
	void update();
}