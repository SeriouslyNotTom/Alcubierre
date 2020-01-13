#pragma once

#include <stdlib.h>
#include <Alcubierre/Libraries/Render/Window/WindowManager.h>

enum Program_Possition {INTRO,INIT,RENDER,PRESENT};

class Static_Flags
{
public:
	bool SteamEnabled = false;
};

class State
{
public:
	bool running = true;
	Program_Possition Possition = Program_Possition::INTRO;
	int _argc;
	char** _argv;
	Static_Flags SFlags = Static_Flags();
	void Intro(int argc, char** argv) { _argc = argc; _argv = argv; }


};

