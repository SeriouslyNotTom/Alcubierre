#include <alcubierre/libraries/io/FileIO.h>

#include <stdlib.h>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <sstream>

using namespace std;

	char* FileIO::GetHomePath()
	{
		return getenv(HOME_PATH);
	}

	char* FileIO::GetGamePath()
	{
		char* homepath = GetHomePath();
		char* gamepath = new char[strlen(homepath) + strlen(GAME_PATH)];
		strcpy(gamepath, homepath);
		strcat(gamepath, GAME_PATH);
		return gamepath;
	}

	char* FileIO::ReadEntireFile(char* file)
	{
		if (!CheckFileExists(file)) { fprintf(stderr, "ReadEntireFile could not find %s", file); }
		ifstream fs(file);
		fs.seekg(0, ios::end);
		int size = fs.tellg();
		fs.seekg(0, ios::beg);
		std::stringstream buffer;
		buffer << fs.rdbuf();
		string thing = buffer.str();
		char* output = strdup(thing.c_str());
		return output;
	}

	bool FileIO::CheckFileExists(char* path)
	{
		struct stat buffer;
		int thing = stat(path, &buffer);
		return thing == 0;
	}