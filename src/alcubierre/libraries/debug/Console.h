#pragma once

#include <vector>
#include <string.h>

class Console
{
	
	std::vector<char*> lol;
	char* inputbuff;
public:
	bool ShouldDraw;
	void Render();
	void Init();
};