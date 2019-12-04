#pragma once

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <mio/mmap.hpp>
#include <algorithm>
#include <fcntl.h>
#include <io.h>

class util_file
{
public:
	static char* LoadFile_ifstream(const char* file_path)
	{
		try
		{
			struct stat buff;
			stat(file_path, &buff);
			std::ifstream FileStream(file_path, std::ios_base::binary);
			FileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			char* buffer = new char[buff.st_size];
			buffer[buff.st_size] = '\0';
			FileStream.read(buffer, buff.st_size);
			fprintf(stdout, "\x1B[36m-------------------------------\n%s\n%s\n-------------------------------\n\033[0m", file_path, buffer);
			return buffer;
		}
		catch (std::ifstream::failure e)
		{
			fprintf(stdout, "FAILED TO READ IFSTREAM: %s, REASON: %s, CODE: %i\n", file_path, e.what(),e.code());
		}
	}
	static char* LoadFile_memorymap(const char* file_path)
	{
		const mio::mmap_source mmap(file_path);
		
		char* data = new char[mmap.size()];
		data[mmap.size()] = '\0';
		memcpy(data, mmap.data(), mmap.size());
		return data;
	}
};