#pragma once

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

class util_file
{
public:
	static char* LoadFile_ifstream(const char* file_path)
	{
		try
		{
			std::ifstream FileStream(file_path, std::ios_base::binary);
			FileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			FileStream.seekg(0,std::ios::end);
			int fsize = FileStream.tellg();
			FileStream.seekg(0, std::ios::beg);
			char* buffer = new char[fsize];
			buffer[fsize] = '\0';
			FileStream.read(buffer, fsize);
			fprintf(stdout, "\x1B[36m-------------------------------\n%s\n%s\n-------------------------------\n\033[0m", file_path, buffer);
			return buffer;
		}
		catch (std::ifstream::failure e)
		{
			fprintf(stdout, "FAILED TO READ IFSTREAM: %s, REASON: %s, CODE: %i\n", file_path, e.what(),e.code());
		}
	}
};