#pragma once

#include <stdlib.h>
#include <iostream>

namespace Alcubierre
{
	namespace Debug
	{
		namespace Log
		{
			static void Info(char* msg)
			{
				fprintf(stdout, "\u001b[32m[LOG::INFO] \u001b[36m%s\u001b[0m\r\n", msg);
			}
			static char* FormatString(char* base_string, char* params ...)
			{

				return "";
			}
		}
	}
}