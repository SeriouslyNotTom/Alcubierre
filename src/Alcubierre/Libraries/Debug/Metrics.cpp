#include <Alcubierre/Libraries/Debug/Metrics.h>
#include <glad/glad.h>

#ifdef _WIN32
#include <Windows.h>
#include <Psapi.h>
#endif // _WIN32


void Debug_Metrics::GLFW3_DONE(Window* window)
{
	this->Monitor_Name = glfwGetMonitorName(window->glfw_monitor);
	const GLFWvidmode* vidmode = glfwGetVideoMode(window->glfw_monitor);
	this->Monitor_Refresh_Rate = vidmode->refreshRate;
	this->Monitor_Scale = window->scaling_factor;
}

int Debug_Metrics::getMemoryUsage()
{
#ifdef _WIN32
	PROCESS_MEMORY_COUNTERS mem_info;
	GetProcessMemoryInfo(GetCurrentProcess(), &mem_info, sizeof(mem_info));
	return	mem_info.WorkingSetSize;
#endif
#ifndef _WIN32
	return 0;
#endif // !_WIN32
}