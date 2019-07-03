#pragma once

#include <alcubierre/libraries/render/WindowManager.h>
#include <GLFW/glfw3.h>

void Window::CenterWindow(GLFWmonitor* monitor)
{
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(glfw_window, (mode->width / 2) - (width_ / 2), (mode->height / 2) - (height_ / 2));
}

Window* WindowManager::newWindow(WindowCreationCallback *wccb)
{
	Window* window = new Window();
	(*wccb)(window);
	window->glfw_window = glfwCreateWindow(window->requested_width_, window->requested_height_, window->window_title_.c_str(), window->glfw_monitor, window->glfw_share_window_);
	glfwGetWindowSize(window->glfw_window,&window->width_,&window->height_);
	return window;
}