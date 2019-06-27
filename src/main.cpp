#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#define GLFW_INCLUDE_NONE
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

//#include <alcubierre/imgui-handler.cpp>
#include <config.h>
#include <alcubierre/settings/entry_settings.cpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cppc/render/window_manager.cpp>
#include <alcubierre/forensics/performance.cpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#ifdef _WIN32
#include <ShellScalingApi.h>
#endif
#include <nlohmann/json.hpp>

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error Code: %i ; %s\n", description);
}

static string log_file = "";

int main(int argc, char *argv[])
{
#ifdef _WIN32	
SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
#endif	
fprintf(stdout, "%s VERSION: %s-%s \n", PROJECT_NAME_READABLE, PROJECT_VER, PROJECT_VER_TYPE);
	fprintf(stdout, "DEAR IMGUI VERSION: %s \n", ImGui::GetVersion());

	auto settings = nlohmann::json::parse("{\"settings\":{\"scale\":2,\"w\":3000,\"h\":2000}}");

	int scaling = settings["settings"]["scale"];

	if (glfwInit())
	{
		fprintf(stdout, "GLFW [%s] LOADED \n", glfwGetVersionString());
		glfwSetErrorCallback(error_callback);
	}
	else {
		::exit(EXIT_FAILURE);
	}

	Window main_window = Window(3000,2000);
	
	main_window.SetTitle(string(PROJECT_NAME_READABLE)+" [" + string(PROJECT_VER)+"-"+string(PROJECT_VER_TYPE)+"]");

	GLFWwindow* raw_window = main_window.GetRawWindow();

	bool show_demo_window = true;

	IMGUI_CHECKVERSION();
	
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(raw_window, true);
	ImGui_ImplOpenGL3_Init("#version 150");

	ImGuiStyle *current_style = &ImGui::GetStyle();
	
	current_style->FrameRounding = 0;
	current_style->WindowRounding = 0;
	current_style->TabRounding = 0;
	current_style->ScrollbarRounding = 0;
	ImGui::GetIO().FontGlobalScale = scaling;
	//doColors();

	glfwSwapInterval(1);

	float f;
	static float color[4] = { 0,0,1,1 };
	bool show_imgui_debug = false;

	while (!glfwWindowShouldClose(raw_window))
	{		
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		
		if (show_demo_window)
		{
			ImGui::SetNextWindowPos(ImVec2(100, 100));
			ImGui::Begin("Demo Window",NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize| ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
			if (ImGui::Button("Show / Hide Test Window"))
			{
				show_imgui_debug = !show_imgui_debug;
			}
			ImGui::ColorEdit4("color", color, ImGuiColorEditFlags_PickerHueWheel);
			ImGui::End();

			if (show_imgui_debug)
			{
				ImGui::ShowDemoWindow(&show_imgui_debug);
			}

		}
		
		ImGui::Render();

		int display_w, display_h;
		glfwGetFramebufferSize(raw_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0.3, 1);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(raw_window);
	}

	glfwTerminate();
	::exit(EXIT_SUCCESS);
}
