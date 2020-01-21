#define GLFW_INCLUDE_NONE
#include <Alcubierre/Alcubierre.h>
#include <Alcubierre/Engine.h>

int Alcubierre::argc = NULL;
char* Alcubierre::argv = NULL;

void Alcubierre::Initialize_Core()
{
	fprintf(stdout, "%s (%s) [%s %s] %s\n\r", PROJECT_NAME_READABLE, PROJECT_OS, PROJECT_VER, PROJECT_VER_TYPE, PROJECT_BUILD_DATE);
	Info = _Info();
	Basic_Config = _Basic_Config();
}

void Alcubierre::Accept_Arguments(int argc, char* argv)
{
	Alcubierre::argc = argc;
	Alcubierre::argv = argv;
}

void Alcubierre::Exit(int code)
{
	fprintf(stdout, "Got Exit Code (%i)\r\n", code);
	exit(code);
}
