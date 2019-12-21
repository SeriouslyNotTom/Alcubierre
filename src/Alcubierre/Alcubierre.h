#pragma once

#include <iostream>
#include <Alcubierre/Tests/TestProgram_handler.h>
#include <Alcubierre/Libraries/Debug/Metrics.h>
#include <Alcubierre/Libraries/Render/Window/WindowManager.h>
#include <Alcubierre/StateManager.h>

class Alcubierre
{
public:
	static TestProgram_handler TestPrograms;
	static Debug_Metrics DebugMetrics;
	static Render_Manager RenderManager;
	static State ProgramState;
};

static Window *my_window;