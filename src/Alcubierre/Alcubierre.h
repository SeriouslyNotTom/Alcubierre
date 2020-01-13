#pragma once
#define GLFW_INCLUDE_NONE
#include <iostream>
#include <Alcubierre/Tests/TestProgram_handler.h>
#include <Alcubierre/Libraries/Debug/Metrics.h>
#include <Alcubierre/Libraries/Render/Window/WindowManager.h>
#include <Alcubierre/StateManager.h>
#include <Alcubierre/Engine.h>

class Alcubierre
{
public:
	static TestProgram_handler TestPrograms;
	static Debug_Metrics DebugMetrics;
	static Render_Manager RenderManager;
	static State ProgramState;
	static Engine _Engine;

	static void Intro(int agc, char **argv);
	static void Init();
	static void Tick();
	static void Cleanup();

};

static Window *my_window;