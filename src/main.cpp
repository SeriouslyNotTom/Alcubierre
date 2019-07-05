#pragma once

#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#define GLFW_INCLUDE_NONE
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <config.h>
#include <alcubierre/forensics/Logging.h>
#include <alcubierre/forensics/Debug.cpp>
#include <alcubierre/libraries/render/WindowManager.h>
#include <alcubierre/libraries/render/RenderManager.h>
#include <alcubierre/libraries/debug/ImGui_Handler.h>
#include <alcubierre/libraries/settings/Settings.h>
#include <alcubierre/libraries/debug/Console.h>

using namespace std;

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error Code: %i ; %s\n", description);
}

Video_Settings VideoSettings;
Console* con;

void ImGui_Callback()
{
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("fuck"))
	{
		ImGui::EndMenu();
	}	
	ImGui::EndMainMenuBar();

	ImGui::ShowDemoWindow();
	con->Render();

}

void windowCreation(Window* win)
{
	win->requested_width_ = VideoSettings.Width;
	win->requested_height_ = VideoSettings.Height;
	win->glfw_monitor = NULL;
	win->window_title_ = PROJECT_NAME_READABLE;
	win->scaling_factor = VideoSettings.ScalingFactor;

	Logger::General(std::to_string(win->requested_width_).c_str());
}

int main(int argc, char *argv[])
{

	if (glfwInit())
	{
		fprintf(stdout, "GLFW [%s] LOADED \n", glfwGetVersionString());
		glfwSetErrorCallback(error_callback);
	}

	char* settings_file = new char[200];
	strcpy(settings_file, getenv("APPDATA"));
	strcat(settings_file, "\\Alcubierre\\settings.json");
	VideoSettings = Settings::LoadSettings(settings_file);

	WindowManager winman = WindowManager();
	Logger::Raw(__FUNCTION__);
	WindowManager::WindowCreationCallback thing = static_cast<WindowManager::WindowCreationCallback>(&windowCreation);
	Window* window = winman.newWindow(&thing);
	GLFWmonitor *primary = glfwGetPrimaryMonitor();
	window->CenterWindow(primary);

	glfwMakeContextCurrent(window->glfw_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		exit(EXIT_FAILURE);
	}

	con = new Console();
	con->Init();

	RenderManager renman;
	renman.mywindow = window;
	ImGui_Handler dear = ImGui_Handler();
	dear.AddFrameStart(*ImGui_Callback);
	renman.Add(&dear);
	renman.Init();

	glfwSwapInterval(0);

	while (!glfwWindowShouldClose(window->glfw_window))
	{
		glfwPollEvents();

		int display_w, display_h;
		glfwGetFramebufferSize(window->glfw_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0.3, 1);

		renman.Render_HOOK();

		glfwSwapBuffers(window->glfw_window); 
	}
}
