#include <Alcubierre/Engine.h>
#include <glad/glad.h>

void error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW3 Error Code: %i ; %s\n", error, description);
}

//i love you c++, i really do (totally not sarcasm)
Window* Alcubierre::Engine::_PrimaryWindow = NULL;
std::unordered_map<char*, Alcubierre::Renderer::RenderQueueOBJ>* Alcubierre::Renderer::RenderQueue = NULL;

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
	Alcubierre::Debug::Log::Info("Spawning Window...");
	Alcubierre::Engine::_PrimaryWindow = WindowManager::newWindow(NewWindowCallback);
	Alcubierre::Engine::SetupContext();
	Alcubierre::Debug::Log::Info("Done");
}

bool Alcubierre::Renderer::Initialize()
{
	Alcubierre::Debug::Log::Info("Renderer Initializing...");
	Alcubierre::Renderer::RenderQueue = new std::unordered_map<char*, RenderQueueOBJ>();
	Alcubierre::Debug::Log::Info("Done");
	return true;
}
