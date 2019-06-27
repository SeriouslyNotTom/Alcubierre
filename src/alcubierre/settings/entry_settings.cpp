#pragma once

#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class entry_settings
{
	void HandleCommandLineArgs(int num_arguments, char*arguments[])
	{
		for (size_t i = 1; i < num_arguments; i++)
		{

			if (strcmp(arguments[i], "-asset_overide") == 0)
			{

			}
			if (strcmp(arguments[i], "-vsync") == 0)
			{

			}
		}
	}
};
