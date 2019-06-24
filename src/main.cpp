#ifdef _WIN32
#define APIENTRY __stdcall
#endif


#define GLFW_INCLUDE_NONE
#define IMGUI_IMPL_OPENGL_LOADER_GLAD


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



//#include <alcubierre/Alcubierre.cpp>

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error Code: %i ; %s\n", description);
}

static string log_file = "";

int main(int argc, char *argv[])
{
	//Alcubierre::init(argc, argv);
	profiler testprof = profiler();
	testprof.in();
	//sharing_is_caring::init();
	//classer.fck = "ah fuck";
	//test tester = test();
	//tester.test_main(argc,argv);
	fprintf(stdout, "%s VERSION: %s-%s \n", PROJECT_NAME_READABLE, PROJECT_VER, PROJECT_VER_TYPE);
	fprintf(stdout, "DEAR IMGUI VERSION: %s \n", ImGui::GetVersion());
	testprof.out();
	uint64_t nanos = testprof.nanos();
	double millis = double(nanos / 1000);
	//fprintf(stdout,"init took %s microseconds \n", to_string(millis).c_str());
	
	
	if (glfwInit())
	{
		fprintf(stdout, "GLFW [%s] LOADED \n", glfwGetVersionString());
		glfwSetErrorCallback(error_callback);
	}
	else {
		exit(EXIT_FAILURE);
	}

	Window main_window = Window(1088, 612);
	
	//Window second_window = Window(600, 480);
	main_window.SetTitle(string(PROJECT_NAME_READABLE)+" [" + string(PROJECT_VER)+"-"+string(PROJECT_VER_TYPE)+"]");

	GLFWwindow* raw_window = main_window.GetRawWindow();

	bool show_metrics_window = false;

	IMGUI_CHECKVERSION();
	
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(raw_window, true);
	ImGui_ImplOpenGL3_Init("#version 150");
	

	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(raw_window))
	{		
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowMetricsWindow(&show_metrics_window);

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
	exit(EXIT_SUCCESS);
}