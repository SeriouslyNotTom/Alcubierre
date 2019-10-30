#pragma once

#include<alcubierre/libraries/render/WindowManager.h>

class Alcubierre_Main
{
public:
	void init(int argc, char *argv[]);

	Alcubierre_Main() {};

};

namespace Alcubierre
{

	extern WindowManager winman;
	void Init();

}