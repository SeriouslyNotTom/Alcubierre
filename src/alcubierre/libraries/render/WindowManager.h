#pragma once

//#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <iostream>

class Window {
private:
	int _xpos, _ypos;
	int _width, _height;
	std::string _window_title;
	GLFWwindow* _glfw_window;
	GLFWmonitor* _glfw_monitor;
	GLFWwindow* _glfw_share_window;
	int _requested_width, _requested_height;
	typedef std::function<void(void)> HintCallback;
	std::vector<HintCallback> _callbacks;
};