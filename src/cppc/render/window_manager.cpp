#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <alcubierre/forensics/Logging.h>

class Window
{

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

	void _InitWindow()
	{
		if (_window_title == "") { _window_title = "WINDOW"; }
		Logger::General("Hinting Window");
		PerformHints();
		Logger::General("glfwCreateWindow");
		_glfw_window = glfwCreateWindow(_requested_width, _requested_height, _window_title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(_glfw_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize OpenGL context" << std::endl;
			exit(EXIT_FAILURE);
		}
		glViewport(0, 0, _width, _height);
		glfwGetWindowSize(_glfw_window, &_width, &_height);
		glfwGetWindowPos(_glfw_window, &_xpos, &_ypos);
		CenterWindow();
	}

	void _FirstHints()
	{
		//glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		//glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
		glfwWindowHint(GLFW_DECORATED, GL_TRUE);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
	}

public:
	Window(int width, int height)
	{
		 _requested_width = width; _requested_height = height;
		_InitWindow();
	}

	Window(int width, int height, void(*ptr)())
	{
		_requested_width = width; _requested_height = height;
		RegisterHintCallback(ptr);
		_InitWindow();
	}

	void SetTitle(std::string title) { _window_title = title; glfwSetWindowTitle(_glfw_window, _window_title.c_str()); }
	std::string GetTitle() { return _window_title; }
	void SetPosition(int x, int y) { _xpos = x; _ypos = y; glfwSetWindowPos(_glfw_window, _xpos, _ypos); }
	void GetPoisiton(int* x, int* y) { glfwGetWindowPos(_glfw_window, &_xpos, &_ypos); *x = _xpos; *y = _ypos; }
	void GetRequestedSize(int* width, int* height) { *width = _requested_width; *height = _requested_height; }
	void GetSize(int* width, int* height) { glfwGetWindowSize(_glfw_window, &_width, &_height); *width = _width; *height = _height; }

	void PerformHints()
	{
		Logger::General("First Hints");
		_FirstHints();
		Logger::General("Hooked Hints");
		//for each (HintCallback cb in _callbacks) { cb(); }
	}
	
	void RegisterHintCallback(const HintCallback &cb)
	{
		_callbacks.push_back(cb);
	}

	bool CenterWindow()
	{
		GLFWmonitor* primary = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(primary);
		glfwSetWindowPos(_glfw_window, (mode->width / 2) - (_width / 2), (mode->height / 2) - (_height / 2));
		return true;
	}

	GLFWwindow* GetRawWindow(){return _glfw_window;}

};

class WindowManager 
{
	
public:	
	
	WindowManager()
	{

	}

};