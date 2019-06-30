#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#define GLFW_INCLUDE_NONE
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

//#include <alcubierre/imgui-handler.cpp>
#include <Windows.h>
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
#include <alcubierre/libraries/io/FileIO.h>
#include <alcubierre/forensics/Logging.h>
#include <alcubierre/libraries/settings/Settings.h>
#include <alcubierre/libraries/render/RenderManager.h>
#include <alcubierre/libraries/debug/ImGui_Handler.h>


void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error Code: %i ; %s\n", description);
}

int main(int argc, char *argv[])
{
#ifdef _WIN32	
SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
#endif	
	fprintf(stdout, "%s VERSION: %s-%s \n", PROJECT_NAME_READABLE, PROJECT_VER, PROJECT_VER_TYPE);
	fprintf(stdout, "DEAR IMGUI VERSION: %s \n", ImGui::GetVersion());
	Logger::General("DEAR IMGUI");
	struct Video_Settings vs;
	vs = Settings::LoadSettings("C:\\Users\\Tom\\AppData\\Roaming\\Alcubierre\\settings.json");
	if (glfwInit())
	{
		fprintf(stdout, "GLFW [%s] LOADED \n", glfwGetVersionString());
		glfwSetErrorCallback(error_callback);
	}
	else {
		::exit(EXIT_FAILURE);
	}

	RenderManager::DoRenders();
	
	Window main_window = Window(vs.Width,vs.Height);
	main_window.SetTitle(string(PROJECT_NAME_READABLE)+" [" + string(PROJECT_VER)+"-"+string(PROJECT_VER_TYPE)+"]");
	GLFWwindow* raw_window = main_window.GetRawWindow();

	bool show_demo_window = true;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(raw_window, true);
	ImGui_ImplOpenGL3_Init("#version 150");
	ImGui::GetIO().FontGlobalScale = vs.ScalingFactor;
	ImGui_Handler::ApplyColors();
	ImGui_Handler::ApplyStyles();

	float f;
	static float color[4] = { 0,0,1,1 };
	bool show_imgui_debug = false;

	char ver_buf[100];
	snprintf(ver_buf,100,"OPENGL VERSION: %s \r", glGetString(GL_VERSION));
	Logger::Raw(ver_buf);
	char hard_buf[100];
	snprintf(hard_buf, 100, "VIDEO HARDWARE: %s %s \r", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	Logger::Raw(hard_buf);

	bool thing = false;

	while (!glfwWindowShouldClose(raw_window))
	{		
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Debug"))
			{
				if (ImGui::BeginMenu("Info"))
				{
					ImGui::Text("this is some text ijih8j38j3j84ht8h48hht84h8ht484ht8ht48ht48h8wwoid");
					ImGui::EndMenu();
				}
				if (ImGui::MenuItem("thing", "things stuff")) {}
				ImGui::Text("test text", "this is test");
				if (ImGui::BeginMenu("Flags"))
				{
					ImGui::MenuItem("Movable", NULL, &thing);
					ImGui::MenuItem("not movable", NULL, true);
					ImGui::EndMenu();
				}
				
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		
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
