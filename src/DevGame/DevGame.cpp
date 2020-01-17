#include <DevGame/DevGame.h>
#include <Alcubierre/Alcubierre.h>
#include <Alcubierre/Engine.h>
#include <GLFW/glfw3.h>

void WindowCallback(Window* window)
{
	window->requested_width_ = 1600;
	window->requested_height_ = 900;
	window->glfw_monitor = NULL;
	window->window_title_ = string(PROJECT_NAME_READABLE);
	window->scaling_factor = 1;
}

int main(int argc, char* argv[])
{
	Alcubierre::Accept_Arguments(argc, *argv);
	Alcubierre::Initialize_Core();
	Alcubierre::Engine::Initialize();
	WindowManager::WindowCreationCallback window_cb = static_cast<WindowManager::WindowCreationCallback>(&WindowCallback);
	Alcubierre::Engine::CreateWindow(&window_cb);

	glfwMakeContextCurrent(Alcubierre::Engine::_PrimaryWindow->glfw_window);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(Alcubierre::Engine::_PrimaryWindow->glfw_window))
	{
		glfwPollEvents();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

		glfwSwapBuffers(Alcubierre::Engine::_PrimaryWindow->glfw_window);
	}

	glfwTerminate();
	Alcubierre::Exit(0);

}