#include <Alcubierre/Engine.h>

void error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW3 Error Code: %i ; %s\n", error, description);
}

//i love you c++, i really do (totally not sarcasm)
Window* Alcubierre::Engine::_PrimaryWindow = NULL;

void Alcubierre::Engine::Initialize()
{
	fprintf(stdout, "GLFW %s\n", glfwGetVersionString());
	glfwSetErrorCallback(&error_callback);
	error_callback(9001, "glfw error code callback test. please ignore");

	if (!glfwInit())
	{
		Alcubierre::Exit(-1);
	}

}

void Alcubierre::Engine::SetupContext()
{
	glfwMakeContextCurrent(Alcubierre::Engine::_PrimaryWindow->glfw_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		Alcubierre::Exit(-1);
	}
}

void Alcubierre::Engine::SpawnWindow(WindowManager::WindowCreationCallback* NewWindowCallback)
{
	Alcubierre::Engine::_PrimaryWindow = WindowManager::newWindow(NewWindowCallback);
	Alcubierre::Engine::SetupContext();
}