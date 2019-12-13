#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <iostream>

class Window {
public:
	int xpos_, ypos_;
	int width_, height_;
	std::string window_title_;
	GLFWwindow* glfw_share_window_;
	int requested_width_, requested_height_;
	typedef std::function<void(void)> HintCallback;
	std::vector<HintCallback> hint_callbacks_;
	GLFWmonitor* glfw_monitor;
	GLFWwindow* glfw_window;
	double scaling_factor;
	void CenterWindow(GLFWmonitor* monitor);

private:

};

class WindowManager {
public:
	const typedef std::function<void(Window*)> WindowCreationCallback;
	static Window* newWindow(WindowCreationCallback* create_callback);
	;
};