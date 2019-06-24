#include <iostream>
#include <alcubierre/settings/general_settings.cpp>
#include <alcubierre/settings/serialization/settingComponentSerializer.cpp>
#include <nlohmann/json.hpp>
#include <string>
#include <memory>

class settings_manager {
	
public:
	general_settings General = general_settings();
	int window_width;
	int window_height;
	string window_mode;

	settings_manager()
	{
		General.enableSteam.SetBool(false);
		General.enableVsync.SetInt(1);
		
	}

};