#pragma once

#include <vector>
#include <string.h>

class Console
{
	
	std::vector<char*> lol;
	char* inputbuff = new char[1024];
public:
	void Render();
	void Init();
};