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
#include <ctime>
#include <chrono>

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
using namespace std::chrono;

bool should_render_ = true;

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error Code: %i ; %s\n", description);
}

void window_iconify_callback(GLFWwindow* window, int iconified)
{
	if (iconified)
	{
		should_render_ = false;
	}
	else {
		should_render_ = true;
	}
}

Video_Settings VideoSettings;
Console* con;
bool Enable_Test01;
bool Init_Test01 = false;
bool ShowMetrics = true;
bool ShowImGUiDemo = false;
bool thing = true;
bool vsync = false;
bool vsync_applied = false;


high_resolution_clock::time_point t1, t2;
duration<double> render_time;
int update_stat = 0;



void ImGui_Callback()
{
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("Debug"))
	{
		ImGui::Checkbox("Console", &con->ShouldDraw);
		ImGui::Checkbox("Metrics", &ShowMetrics);
		ImGui::Checkbox("ImGui Demo", &ShowImGUiDemo);
		ImGui::EndMenu();
	}	
	if (ImGui::BeginMenu("Tests"))
	{
		ImGui::Checkbox("Test01", &Enable_Test01);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Video"))
	{
		ImGui::Checkbox("VSYNC", &vsync);
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	con->Render();
	if (ShowMetrics) { ImGui::ShowMetricsWindow(&ShowMetrics); }
	if (ShowImGUiDemo) { ImGui::ShowDemoWindow(&ShowImGUiDemo); }

	ImGui::Begin("MS WINDOW");
	ImGui::Text(to_string((render_time.count() * 1000)).c_str());
	ImGui::End();

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

float counter = -1.0f;

GLuint VAO1;
GLfloat vbd[] =
{
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
};
GLuint vrtbuf;

void Test01_Init()
{
	glGenVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);
	
	glGenBuffers(1, &vrtbuf);
	glBindBuffer(GL_ARRAY_BUFFER, vrtbuf);
	
}

void Test01_Render()
{
	vbd[7] = counter;
	if (counter >= 1.0f) { counter = -1.0f; }
	counter = counter + 0.005f;
	glBufferData(GL_ARRAY_BUFFER, sizeof(vbd), &vbd, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vrtbuf);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
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
	
	glfwSetWindowIconifyCallback(window->glfw_window, window_iconify_callback);

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

		t1 = high_resolution_clock::now();
		if (should_render_)
		{
			
			if (Enable_Test01) {
				if (Init_Test01 == true) { Test01_Render(); }
				else { Test01_Init(); Init_Test01 = true; }
			}
			
			
			renman.Render_HOOK();
			
		}
		t2 = high_resolution_clock::now();
		glfwSwapBuffers(window->glfw_window); 
		

		update_stat++;
		if(update_stat>10)
		{ 
			render_time = duration_cast<duration<double>>(t2 - t1);
			update_stat = 0;
		}
		
	}
}