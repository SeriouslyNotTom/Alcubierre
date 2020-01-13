#define GLFW_INCLUDE_NONE
#include <Alcubierre/Alcubierre.h>
#include <Alcubierre/StateManager.h>
#include <config.h>

State Alcubierre::ProgramState = State();
Debug_Metrics Alcubierre::DebugMetrics;
Render_Manager Alcubierre::RenderManager;

void Alcubierre::Init()
{
	Alcubierre::ProgramState.Possition = Program_Possition::INIT;
	fprintf(stdout, "ALCUBIERRE::INIT\r\n");
}

void Alcubierre::Tick()
{
	fprintf(stdout, "I'm Ticking right now\r\n");
}

void Alcubierre::Cleanup()
{

}

void Alcubierre::Intro(int argc, char **argv)
{
	fprintf(stdout, "%s (%s) [%s %s] %s\n\r", PROJECT_NAME_READABLE, PROJECT_OS, PROJECT_VER, PROJECT_VER_TYPE, PROJECT_BUILD_DATE);
	fprintf(stdout, "GLFW %s\n\r", glfwGetVersionString());
	Alcubierre::ProgramState.Intro(argc, argv);
	Alcubierre::ProgramState.Possition = Program_Possition::INTRO;
	fprintf(stdout, "ALCUBIERRE::INTRO\r\n");

	

	Alcubierre::Init();
	while (ProgramState.running)
	{
		Alcubierre::Tick();
	}
	Alcubierre::Cleanup();

}