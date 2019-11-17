#define GLFW_INCLUDE_NONE
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <main.h>
#include <stdlib.h>
#include <iostream>

#include <config.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <Alcubierre/Libraries/Render/RenderManager.h>
#include <Alcubierre/Libraries/Render/Window/WindowManager.h>
#include <Alcubierre/Libraries/Debug/ImGui_handler.h>
#include <Alcubierre/Libraries/Utilities/color.h>
#include <Alcubierre/Libraries/Debug/Debug_interface.h>
#include <Alcubierre/Tests/TestProgram_handler.h>
#include <Alcubierre/Tests/Demos.cpp>
#include <Alcubierre/Libraries/Debug/Metrics.h>


using namespace std;

typedef void(*FPTR)();

void error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW3 Error Code: %i ; %s\n", error, description);
}



void CreateWindow_Callback(Window* window)
{
	window->requested_width_ = 1600;
	window->requested_height_ = 900;
	window->glfw_monitor = NULL;
	window->window_title_ = string("Alcubierre");
	window->scaling_factor = 1;
#ifdef __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif // __APPLE__
}

class fuckyinterface : public ImGui_Render
{
	void ImGuiFrameStart()
	{
		Debug_Interface::ImGuiFrameStart();
	}
};

TestProgram_handler Alcubierre::Test_Programs = TestProgram_handler();
Demos Demo_Programs = Demos();
Debug_Metrics Alcubierre::DebugMetrics = Debug_Metrics();

int main(int argc, char *argv[])
{
	fprintf(stdout,"%s (%s) [%s %s] %s\n",PROJECT_NAME_READABLE, PROJECT_OS, PROJECT_VER, PROJECT_VER_TYPE, PROJECT_BUILD_DATE);
	fprintf(stdout, "GLFW %s\n",glfwGetVersionString());

	glfwSetErrorCallback(&error_callback);
	
	if(!glfwInit())
		return -1;

	WindowManager::WindowCreationCallback Window_Created_CB = static_cast<WindowManager::WindowCreationCallback>(&CreateWindow_Callback);
	Window* window = WindowManager::newWindow(&Window_Created_CB);
	Alcubierre::DebugMetrics.GLFW3_DONE(window);
	GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
	window->CenterWindow(primary_monitor);

	RenderManager renderMan = RenderManager();
	renderMan.myWindow = window;

	ImGui_Handler dearImGui = ImGui_Handler();
	fuckyinterface fckint = fuckyinterface();
	dearImGui.AddImGuiRenderableOBJ(&fckint);
	
	
	dearImGui.AddImGuiRenderableOBJ(&Alcubierre::Test_Programs);
	Debug_Interface::AddDebugMenuHook(&Alcubierre::Test_Programs);
	renderMan.Add(&Alcubierre::Test_Programs);
	renderMan.Add(&dearImGui);
	float xscale, yscale;
	std::string monitor_name;
	monitor_name = glfwGetMonitorName(window->glfw_monitor);
	glfwGetWindowContentScale(window->glfw_window, &xscale, &yscale);
	fprintf(stdout, "Content scale for monitor: %s is x : %f and y : %f\n", monitor_name, xscale, yscale);
	

	glfwMakeContextCurrent(window->glfw_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{

		std::cout << "Failed to initialize OpenGL context" << std::endl;
		exit(EXIT_FAILURE);
	}

	const char* GLVer = (char*)glGetString(GL_VERSION);
	const char* GLRenderer = (char*)glGetString(GL_RENDERER);
	fprintf(stdout, "OPENGL %s %s\n", GLVer, GLRenderer);
	
	Alcubierre::DebugMetrics.GPU_NAME = GLRenderer;
	Alcubierre::DebugMetrics.OPENGL_VER = GLVer;
	Demo_Programs.LoadTestPrograms();

	renderMan.Init();
	glfwSwapInterval(1);

	RGBA bg_col = Colors::To_Normalized(Colors::JAPANESE_INDIGO);

	while(!glfwWindowShouldClose(window->glfw_window))
	{
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwPollEvents();
		int display_w, display_h;
		glfwGetFramebufferSize(window->glfw_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(bg_col.R,bg_col.G,bg_col.B,bg_col.A);
		
		renderMan.Render_HOOK();

		glfwSwapBuffers(window->glfw_window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}

