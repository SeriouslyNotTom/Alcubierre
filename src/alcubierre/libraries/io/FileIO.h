#pragma once

#ifdef _WIN32
#define HOME_PATH "USERPROFILE"
#define GAME_PATH "\\Documents\\Alcubierre\\"
#define SETTINGS_FILE "settings.json"
#endif
#ifdef linux
#define HOME_PATH "HOME"
#endif

#define ASSET_PATH "fuckme"

#include <string>
#include <stdlib.h>

class FileIO
{
public:
	static char* GetHomePath();
	static char* GetGamePath();
	static char* ReadEntireFile(char* file);
	static bool CheckFileExists(char* path);
};