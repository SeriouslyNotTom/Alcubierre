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

using namespace Alcubierre::Engine::Window;

void WindowCallback(WindowInstance* window)
{
	window->window_width = 1600;
	window->window_height = 900;
	window->glfw_monitor = NULL;
	window->window_title = PROJECT_NAME_READABLE;
	#if defined(__linux__) || defined(__APPLE__)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#endif
}

class ImGuiDemo : public ImGui_Render
{
	void ImGuiFrameStart() 
	{
		ImGui::ShowDemoWindow(NULL);
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

	Alcubierre::Render::Text(1, 1, "fuck");

	ImGuiInstance.AcceptWindow(Alcubierre::Engine::PrimaryWindow);
	ImGuiInstance.Init();

	ImGuiDemo imdemo = ImGuiDemo();
	ImGuiInstance.AddImGuiRenderableOBJ(&imdemo);

	Alcubierre::Renderer::Initialize();

	glfwMakeContextCurrent(Alcubierre::Engine::PrimaryWindow->glfw_window);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(Alcubierre::Engine::PrimaryWindow->glfw_window))
	{
		glfwPollEvents();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

		ImGuiInstance.OnRender();

		glfwSwapBuffers(Alcubierre::Engine::PrimaryWindow->glfw_window);
	}

	glfwTerminate();
	Alcubierre::Exit(0);

}
