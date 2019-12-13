#include <Alcubierre/Libraries/Render/Window/WindowManager.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void Window::CenterWindow(GLFWmonitor* monitor)
{
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(glfw_window, (mode->width / 2) - (width_ / 2), (mode->height / 2) - (height_ / 2));
}

Window* WindowManager::newWindow(WindowCreationCallback* wccb)
{
	Window* window = new Window();
	(*wccb)(window);
	window->glfw_window = glfwCreateWindow(window->requested_width_, window->requested_height_, window->window_title_.c_str(), window->glfw_monitor, window->glfw_share_window_);
	glfwGetWindowSize(window->glfw_window, &window->width_, &window->height_);
	//allan please add code to detect which monitor the progam is running in, and maybe add that to a helper class
	window->glfw_monitor = glfwGetPrimaryMonitor();
	float xscale, yscale;
	glfwGetMonitorContentScale(window->glfw_monitor, &xscale, &yscale);
	window->scaling_factor = yscale;
	return window;
}