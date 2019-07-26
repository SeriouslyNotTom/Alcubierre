#include <alcubierre/libraries/settings/Settings.h>

#include <alcubierre/forensics/Logging.h>
#include <alcubierre/libraries/io/FileIO.h>
#include <nlohmann/json.hpp>

Video_Settings Settings::LoadSettings(char* path)
{
	struct Video_Settings vs;
	//char* file = FileIO::ReadEntireFile(path);
	//Logger::General("Loading Settings.json");
	//auto settings = nlohmann::json::parse(file);
	//defaults
	vs.ScalingFactor = 1.25;
	vs.Width = 1600;
	vs.Height = 900;
	//loaded - maybe
	//vs.ScalingFactor = settings["settings"]["scaling"];
	//vs.Width = settings["settings"]["width"];
	//vs.Height = settings["settings"]["height"];
	return vs;
}