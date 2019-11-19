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
		std::ifstream FileStream;
		int fsize;
		FileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			FileStream.open(file_path);
			FileStream.seekg(0,FileStream.end);
			fsize = FileStream.tellg();
			FileStream.seekg(0, FileStream.beg);
			std::stringstream buffer;
			buffer << FileStream.rdbuf();
			std::string data = buffer.str();
			char* output = strdup(data.c_str());
			FileStream.close();
			fprintf(stdout, "\x1B[36m-------------------------------\n%s\n%s\n-------------------------------\n\033[0m", file_path, output);
			return output;
		}
		catch (std::ifstream::failure e)
		{
			fprintf(stdout, "FAILED TO READ IFSTREAM: %s, REASON: %s, CODE: %i\n", file_path, e.what(),e.code());
		}
	}
};