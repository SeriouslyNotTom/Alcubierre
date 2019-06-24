#include <stddef.h>
#include <string.h>
#include <iostream>

using namespace std;

class base_settings
{
public:
	enum Video_Mode {WINDOWED,FULLSCREEN,BORDERLESS_FULLSCREEN};

private:
	Video_Mode _videomode;

public:

	//io functions
	void LoadFromJSON(std::string json_data)
	{

	}

	void LoadFromJSONFile(std::string json_data_file_path)
	{

	}

	//manual get/sets
	Video_Mode getVideoMode()
	{
		return _videomode;
	}
	
};