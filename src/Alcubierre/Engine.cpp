#include <Alcubierre/Engine.h>
#include <glad/glad.h>

void error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW3 Error Code: %i ; %s\n", error, description);
}

//i love you c++, i really do (totally not sarcasm)
Alcubierre::Engine::Window::WindowInstance* Alcubierre::Engine::PrimaryWindow = NULL;
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
	glfwMakeContextCurrent(Alcubierre::Engine::PrimaryWindow->glfw_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		Alcubierre::Exit(-1);
	}
}

void Alcubierre::Engine::SpawnWindow(Window::WindowCreationCallback* NewWindowCallback)
{
	Alcubierre::Debug::Log::Info("Spawning Window...");
	Alcubierre::Engine::PrimaryWindow = Window::createWindow(NewWindowCallback);
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

void Alcubierre::Engine::Window::WindowInstance::CenterWindow()
{
	CenterWindow(glfwGetPrimaryMonitor());
}

void Alcubierre::Engine::Window::WindowInstance::CenterWindow(GLFWmonitor* monitor)
{
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(glfw_window, (mode->width / 2) - (window_width / 2), (mode->height / 2) - (window_height / 2));
}

Alcubierre::Engine::Window::WindowInstance* Alcubierre::Engine::Window::createWindow(WindowCreationCallback* window_cb)
{
	using namespace Alcubierre::Engine::Window;
	WindowInstance* Window = new WindowInstance();
	(*window_cb)(Window);
	Window->glfw_window = glfwCreateWindow(Window->window_width, Window->window_height, Window->window_title, Window->glfw_monitor, Window->glfw_share_window);
	glfwGetWindowSize(Window->glfw_window, &Window->window_width, &Window->window_height);
	//allan please add code to detect which monitor the progam is running in, and maybe add that to a helper class
	Window->glfw_monitor = glfwGetPrimaryMonitor();
	float xscale, yscale;
	return Window;
}
