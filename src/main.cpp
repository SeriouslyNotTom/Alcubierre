#define GLFW_INCLUDE_NONE
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <main.h>
#include <stdlib.h>
#include <iostream>

#include <config.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Alcubierre/Libraries/Utilities/lodepng.h>
#include <Alcubierre/Libraries/Render/RenderManager.h>
#include <Alcubierre/Libraries/Render/Window/WindowManager.h>
#include <Alcubierre/Libraries/Debug/ImGui_handler.h>
#include <Alcubierre/Libraries/Utilities/color.h>
#include <Alcubierre/Libraries/Debug/Debug_interface.h>
#include <Alcubierre/Tests/TestProgram_handler.h>
#include <Alcubierre/Tests/Demos.cpp>
#include <Alcubierre/Libraries/Debug/Metrics.h>
#include <Alcubierre/Libraries/Utilities/file.h>
#include <Alcubierre/Libraries/Render/Shader.h>


using namespace std;
using namespace glm;

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
	window->window_title_ = string(PROJECT_NAME_READABLE);
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
RenderManager Alcubierre::Render_Manager = RenderManager();

int main(int argc, char *argv[])
{
	fprintf(stdout,"%s (%s) [%s %s] %s\n",PROJECT_NAME_READABLE, PROJECT_OS, PROJECT_VER, PROJECT_VER_TYPE, PROJECT_BUILD_DATE);
	fprintf(stdout, "GLFW %s\n",glfwGetVersionString());

	glfwSetErrorCallback(&error_callback);
	
	if(!glfwInit())
		return -1;

	//char* testimage = util_file::LoadFile_ifstream("C:\\Users\\tom\\Documents\\Github\\Alcubierre\\output\\runtime\\assets\\ico.png");
	std::vector<unsigned char> data;
	std::vector<unsigned char> image_large;
	std::vector<unsigned char> image_smol;

	lodepng::load_file(data, "C:\\Users\\tom\\Documents\\Github\\Alcubierre\\output\\runtime\\assets\\ico.png");
	unsigned width_large, height_large;
	lodepng::decode(image_large, width_large, height_large, data);
	unsigned width_smol, height_smol;
	data.clear();
	lodepng::load_file(data, "C:\\Users\\tom\\Documents\\Github\\Alcubierre\\output\\runtime\\assets\\ico_smol.png");
	lodepng::decode(image_smol, width_smol, height_smol, data);
	data.clear();

	GLFWimage icons[2];
	
	icons[0].height = height_large;
	icons[0].width = width_large;
	icons[0].pixels = image_large.data();

	icons[1].height = height_smol;
	icons[1].width = width_smol;
	icons[1].pixels = image_smol.data();
	//image.clear();
	

	WindowManager::WindowCreationCallback Window_Created_CB = static_cast<WindowManager::WindowCreationCallback>(&CreateWindow_Callback);
	Window* window = WindowManager::newWindow(&Window_Created_CB);
	Alcubierre::DebugMetrics.GLFW3_DONE(window);
	GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
	window->CenterWindow(primary_monitor);

	glfwSetWindowIcon(window->glfw_window, 2, icons);

	Alcubierre::Render_Manager.myWindow = window;

	ImGui_Handler dearImGui = ImGui_Handler();
	fuckyinterface fckint = fuckyinterface();
	dearImGui.AddImGuiRenderableOBJ(&fckint);
	dearImGui.AddImGuiRenderableOBJ(&Alcubierre::Test_Programs);
	Debug_Interface::AddDebugMenuHook(&Alcubierre::Test_Programs);
	Alcubierre::Render_Manager.Add(&dearImGui);
	Alcubierre::Render_Manager.Add(&Alcubierre::Test_Programs);
	
	float xscale, yscale;
	std::string monitor_name;
	monitor_name = glfwGetMonitorName(window->glfw_monitor);
	glfwGetWindowContentScale(window->glfw_window, &xscale, &yscale);
	fprintf(stdout, "Content scale for monitor: %s is x : %f and y : %f\n", monitor_name.c_str(), xscale, yscale);
	
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

	Alcubierre::Render_Manager.Init();
	glfwSwapInterval(1);

	RGBA bg_col = Colors::To_Normalized(Colors::JAPANESE_INDIGO);
	
	Alcubierre::Render_Manager.AddShader(string("Standard"),"C:\\Users\\tom\\Documents\\Github\\Alcubierre\\output\\runtime\\assets\\standard.vshad","C:\\Users\\tom\\Documents\\Github\\Alcubierre\\output\\runtime\\assets\\standard.fshad");

	while(!glfwWindowShouldClose(window->glfw_window))
	{
		
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glfwPollEvents();
		int display_w, display_h;
		glfwGetFramebufferSize(window->glfw_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(bg_col.R,bg_col.G,bg_col.B,bg_col.A);
		
		Alcubierre::Render_Manager.Render_HOOK();

		glfwSwapBuffers(window->glfw_window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}

