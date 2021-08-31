#include <Alcubierre/Libraries/Window.h>
#include <GLFW/glfw3.h>
#include <Vectors.h>

using namespace Alcubierre::Engine;

std::vector<Window::internal_WindowInstance*> Window::window_internal_instances_;
int Window::Window_count = 0;

#pragma region ALCB_WINDOW IMPLEMENTATION

void Alcubierre::Engine::Window::ALCB_Window::setWindowSize(Vector2 window_size)
{
	glfwSetWindowSize(cachedproperties.glfwWindow, window_size.x, window_size.y);
	cachedproperties.window_size = window_size;
}

Vector2 Alcubierre::Engine::Window::ALCB_Window::getWindowSize()
{
	return cachedproperties.window_size;
}

GLFWwindow* Alcubierre::Engine::Window::ALCB_Window::getGLFWWindowPtr()
{
	return cachedproperties.glfwWindow;
}

Vector2 Alcubierre::Engine::Window::ALCB_Window::centreWindow(GLFWmonitor* monitor)
{
	Vector2 new_pos;
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(cachedproperties.glfwWindow, (mode->width / 2) - (cachedproperties.window_size.x / 2), (mode->height / 2) - (cachedproperties.window_size.y / 2));

	return new_pos;
}

Window::ALCB_Window::ALCB_Window(Window::internal_WindowInstance* instance, Window::Window_cachedproperties cachedprops)
{
	this->cachedproperties = cachedprops;
	this->instance_ = instance;
}

#pragma endregion

#pragma region ENGINE::WINDOW IMPLEMENTATION

void Window::glfw_error_callback(int error, const char* error_desc)
{

}

void window_update_loop()
{
	for each (Window::internal_WindowInstance * var in Window::window_internal_instances_)
	{
		glfwSwapBuffers(var->glfw_window);
	}

	glfwPollEvents();
}

void Window::init()
{
	glfwSetErrorCallback(&Window::glfw_error_callback);
	if (glfwInit())
	{
		std::function<void()> updateptr = &window_update_loop;
		Alcubierre::addHook(updateptr);
	}
}



Window::ALCB_Window Window::CreateWindow(Window::WindowInstance_CreationOptions start_opts)
{
	Window::Window_cachedproperties cachedprops;
	Window::internal_WindowInstance new_instance;
	new_instance.creation_opts = start_opts;
	Window::WindowInstance_CreationOptions* opts = &new_instance.creation_opts;

	if (opts->start_fullscreen==true && opts->glfw_monitor == NULL){opts->glfw_monitor = glfwGetPrimaryMonitor();}

	glfwWindowHint(GLFW_VISIBLE, opts->start_visible);
	glfwWindowHint(GLFW_MAXIMIZED, opts->start_maximized);
	glfwWindowHint(GLFW_RESIZABLE, opts->start_resizable);
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, opts->pull_focus_on_launch);
	glfwWindowHint(GLFW_CENTER_CURSOR, opts->start_cursor_centred);

	GLFWwindow* glfw_window = glfwCreateWindow(opts->starting_resolution.x, opts->starting_resolution.y, opts->window_title, opts->glfw_monitor, opts->share_window);

	new_instance.glfw_monitor = opts->glfw_monitor;
	new_instance.glfw_window = glfw_window;
	Window::Window_count++;
	new_instance.window_id = Window::Window_count;
	new_instance.glfw_share_window = opts->share_window;
	glfwSetWindowTitle(glfw_window, opts->window_title);

	Window::window_internal_instances_.push_back(&new_instance);
	cachedprops.fullscreen = opts->start_fullscreen;
	cachedprops.glfwMonitor = opts->glfw_monitor;
	cachedprops.glfwWindow = glfw_window;
	cachedprops.maximized = opts->start_maximized;
	cachedprops.window_size = opts->starting_resolution;
	
	Window::ALCB_Window newWindow = Window::ALCB_Window(&new_instance, cachedprops);
	return newWindow;
}

Window::ALCB_Window Window::CreateWindow()
{
	return Window::CreateWindow(Window::WindowInstance_CreationOptions{});
}

#pragma endregion
