#include <Alcubierre/Libraries/Debug/Metrics.h>
#include <glad/glad.h>

void Debug_Metrics::GLFW3_DONE(Window* window)
{
	this->Monitor_Name = glfwGetMonitorName(window->glfw_monitor);
	const GLFWvidmode* vidmode = glfwGetVideoMode(window->glfw_monitor);
	this->Monitor_Refresh_Rate = vidmode->refreshRate;
	this->Monitor_Scale = window->scaling_factor;
}
