#include <iostream>
#include <alcubierre/settings/settingComponent.cpp>

using namespace std;

class general_settings
{
public:
	settingComponent enableSteam = settingComponent("enableSteam", "enables or disables steam api intergration");
	settingComponent enableVsync = settingComponent("enableVsync", "Vsync on or off");

	general_settings()
	{
		enableSteam.SetBool(false);
		enableVsync.SetInt(1);
	}
};