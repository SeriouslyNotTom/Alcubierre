#include <DevGame/DevGame.h>
#include <Alcubierre/Alcubierre.h>
#include <Alcubierre/Engine.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Alcubierre/Render/Primative.h>
#include <Alcubierre/Render/Text.h>
#include <Alcubierre/Libraries/Debug/ImGui_Handler.h>
#define ASIO_NO_WIN32_LEAN_AND_MEAN
#include <Alcubierre/Engine.h>
#include <stdlib.h>
#include <imgui.h>
//#include <phonon.h>

using namespace Alcubierre::Engine::Window;

void WindowCallback(WindowInstance* window)
{
	window->window_width = 1600;
	window->window_height = 900;
	window->glfw_monitor = NULL;
	window->window_title = PROJECT_NAME_READABLE;
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, false);
	#if defined(__linux__) || defined(__APPLE__)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#endif
}

float clear_col[4];

class ImGuiDemo : public ImGui_Render
{
	void ImGuiFrameStart() 
	{
		ImGui::ShowDemoWindow(NULL);

		if (ImGui::Begin("Renderer Test", NULL))
		{
			ImGui::ColorPicker4("clear color", clear_col);
			ImGui::Checkbox("Debug Mode", &Alcubierre::Debug_Mode);
			ImGui::Text("List Size {0}", Alcubierre::Renderer::RenderQueue->size());
			if (ImGui::Button("Rebuild List")) { Alcubierre::Renderer::RebuildList(); }
			ImGui::End();
		}

		

	};
	void ImGuiFrameEnd() {};
};

ImGui_Handler ImGuiInstance = ImGui_Handler();

int main(int argc, char* argv[])
{
	Alcubierre::Accept_Arguments(argc, *argv);
	Alcubierre::Initialize_Core();
	Alcubierre::Engine::Initialize();
	WindowCreationCallback window_cb = static_cast<WindowCreationCallback>(&WindowCallback);
	Alcubierre::Engine::SpawnWindow(&window_cb);

	Alcubierre::Render::Text(1, 1, "niceword");

	auto const samplingrate = 44100;
	auto const framesize = 1024;

	clear_col[0] = 0.07843137254901960784313725490196f; clear_col[1] = 0.0f; clear_col[2] = 0.15686274509803921568627450980392f; clear_col[3] = 1.0f;

	ImGuiInstance.AcceptWindow(Alcubierre::Engine::PrimaryWindow);
	ImGuiInstance.Init();

	ImGuiDemo imdemo = ImGuiDemo();
	ImGuiInstance.AddImGuiRenderableOBJ(&imdemo);

	Alcubierre::Renderer::Initialize();

	glfwMakeContextCurrent(Alcubierre::Engine::PrimaryWindow->glfw_window);
	glfwSwapInterval(0);

	glfwShowWindow(Alcubierre::Engine::PrimaryWindow->glfw_window);

	while (!glfwWindowShouldClose(Alcubierre::Engine::PrimaryWindow->glfw_window))
	{
		glfwPollEvents();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearColor(clear_col[0], clear_col[1], clear_col[2], clear_col[3]);

		ImGuiInstance.OnRender();

		glfwSwapBuffers(Alcubierre::Engine::PrimaryWindow->glfw_window);
	}

	glfwTerminate();
	Alcubierre::Exit(0);

}
