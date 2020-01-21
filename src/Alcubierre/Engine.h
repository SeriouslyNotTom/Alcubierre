#pragma once
#include <Alcubierre/Alcubierre.h>

class _Render
{
public:
	enum _WindowModes { Fullscreen, Windowed, Borderless_Fullscreen };
	_WindowModes WindowMode;



};

class _StaticFlags
{
public:
	bool SteamEnabled = false;
};

class _Engine
{
public:
	static _Render Render;
	static _StaticFlags StaticFlags;

	void Initialize();
};

namespace Alcubierre
{
	namespace Engine
	{
		void Initialize();
		extern Window* _PrimaryWindow;
		void SpawnWindow(WindowManager::WindowCreationCallback* NewWindowCallback);
		void SetupContext();
	}
}