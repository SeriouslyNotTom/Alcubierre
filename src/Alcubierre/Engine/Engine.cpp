#include <Alcubierre/Engine/Engine.h>
#include <unordered_map>
#include <glad/glad.h>
#include <Alcubierre/Debug/Util.h>

using namespace Alcubierre;

void error_callback(int error, const char* description)
{
	Alcubierre::Debug::Log::Msg("Alcubierre","GLFW3 Error Code: %i ; %s", error, description);
}

//i love you c++, i really do (totally not sarcasm)

std::unordered_map<char*, Alcubierre::Renderer::RenderQueueOBJ*>* Alcubierre::Renderer::RenderQueue = NULL;
std::vector<Alcubierre::Renderer::IRenderable*> *Alcubierre::Renderer::RenderPointerQueue = NULL;

void Alcubierre::Engine::Initialize()
{
	Alcubierre::Debug::Log::Msg("Alcubierre","GLFW %s", glfwGetVersionString());
	glfwSetErrorCallback(&error_callback);
	error_callback(9001, "glfw error code callback test. please ignore");

	if (!glfwInit())
	{
		Alcubierre::Exit(-1);
	}

}

void Alcubierre::Engine::SetupContext()
{
	/*glfwMakeContextCurrent(Alcubierre::Engine::PrimaryWindow->glfw_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Alcubierre::Debug::Log::Msg("Error", "Failed to create OpenGL Context");
		Alcubierre::Exit(-1);
	}*/
}

void Alcubierre::Engine::Tick()
{

}

bool Alcubierre::Renderer::Initialize()
{
	Alcubierre::Debug::Log::Msg("Alcubierre","Renderer Initializing...");
	Alcubierre::Renderer::RenderQueue = new std::unordered_map<char*, RenderQueueOBJ*>();
	Alcubierre::Debug::Log::Msg("Alcubierre","Done");
	Alcubierre::Renderer::RenderPointerQueue = new std::vector<IRenderable*>();
	return true;
}

void Alcubierre::Renderer::RebuildList()
{
	Alcubierre::Debug::Break();
	RenderPointerQueue->clear();

	for (std::pair<char*, RenderQueueOBJ*> obj : *Alcubierre::Renderer::RenderQueue)
	{
		if (obj.second->PreRenderHook.size() > 0)
		{
			for (int i = 0; obj.second->PreRenderHook.size() >= i; i++)
			{
				RenderPointerQueue->push_back(obj.second->PreRenderHook[i]);
			}
		}
		RenderPointerQueue->push_back(obj.second->IOBJ);
	}
}

void Alcubierre::Renderer::AddToQueue(IRenderable RenderableOBJ)
{
}

//void Alcubierre::Engine::Window::WindowInstance::CenterWindow()
//{
//	CenterWindow(glfw_monitor);
//}
//
//void Alcubierre::Engine::Window::WindowInstance::CenterWindow(GLFWmonitor* monitor)
//{
//	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
//	glfwSetWindowPos(glfw_window, (mode->width / 2) - (window_width / 2), (mode->height / 2) - (window_height / 2));
//}

void ALCB_Engine::init()
{
	taskman = Alcubierre::ALCB_Task_Manager();
	
}

void ALCB_Engine::registerTask(ALCB_TASK* task)
{
	taskman.addTask(task);
}

void ALCB_Engine::tick()
{
	taskman.Tick();
}