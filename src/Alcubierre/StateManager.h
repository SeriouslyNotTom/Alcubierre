#include <stdlib.h>
#include <string>
#include <Alcubierre/Libraries/Render/Window/WindowManager.h>

enum Program_State {INTRO,INIT,RENDER,PRESENT};

class Static_Flags
{
public:
	bool SteamEnabled = false;
};

class State
{
public:
	Program_State ProgramState = Program_State::INTRO;
	int argc;
	char** argv;
	Static_Flags SFlags = Static_Flags();
};

