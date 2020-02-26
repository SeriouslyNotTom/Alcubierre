#include <DevGame/DevGame.h>
#include <Alcubierre/Alcubierre.h>
#include <Alcubierre/Engine.h>
#include <GLFW/glfw3.h>
#include <Alcubierre/Render/Primative.h>
#include <Alcubierre/Render/Text.h>
#include <Alcubierre/Libraries/Debug/ImGui_Handler.h>
#define ASIO_NO_WIN32_LEAN_AND_MEAN
#include <Alcubierre/Engine.h>
#include <stdlib.h>
#include <imgui.h>

void WindowCallback(Window* window)
{
	window->requested_width_ = 1600;
	window->requested_height_ = 900;
	window->glfw_monitor = NULL;
	window->window_title_ = std::string(PROJECT_NAME_READABLE);
	window->scaling_factor = 1;
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
	WindowManager::WindowCreationCallback window_cb = static_cast<WindowManager::WindowCreationCallback>(&WindowCallback);
	Alcubierre::Engine::SpawnWindow(&window_cb);

	Alcubierre::Render::Text(1, 1, "fuck");

	ImGuiInstance.AcceptWindow(Alcubierre::Engine::_PrimaryWindow);
	ImGuiInstance.Init();

	ImGuiDemo imdemo = ImGuiDemo();
	ImGuiInstance.AddImGuiRenderableOBJ(&imdemo);

	Alcubierre::Renderer::Initialize();

	glfwMakeContextCurrent(Alcubierre::Engine::_PrimaryWindow->glfw_window);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(Alcubierre::Engine::_PrimaryWindow->glfw_window))
	{
		glfwPollEvents();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

		ImGuiInstance.Render();

		glfwSwapBuffers(Alcubierre::Engine::_PrimaryWindow->glfw_window);
	}

	glfwTerminate();
	Alcubierre::Exit(0);

}