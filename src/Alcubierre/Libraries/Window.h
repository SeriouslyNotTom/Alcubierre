#pragma once

#include <Alcubierre/Alcubierre.h>
#include <Vectors.h>

namespace Alcubierre
{
	namespace Engine
	{
		namespace Window
		{

			struct WindowInstance_CreationOptions
			{
				bool start_visible = true;
				bool start_resizable = false;
				bool start_fullscreen = false;
				bool start_maximized = false;
				bool start_cursor_centred = false;
				bool transparent_framebuffer = false;
				bool pull_focus_on_launch = false;
				Vector2 starting_resolution = { 960,540 };
				GLFWmonitor* glfw_monitor = NULL;
				GLFWwindow* share_window = NULL;
				char* window_title = "Alcubierre\n";
			};

			struct internal_WindowInstance
			{
				WindowInstance_CreationOptions creation_opts;
				GLFWmonitor* glfw_monitor;
				GLFWwindow* glfw_window;
				GLFWwindow* glfw_share_window;
				int window_id;
			};

			struct Window_cachedproperties
			{
				Vector2 window_size;
				bool fullscreen;
				bool maximized;
				GLFWwindow* glfwWindow;
				GLFWmonitor* glfwMonitor;
			};

			class ALCB_Window
			{
			private:
				Window_cachedproperties cachedproperties;
				internal_WindowInstance* instance_;

			public:
				ALCB_Window(internal_WindowInstance* instance, Window_cachedproperties cachedprops);
				
				void setWindowSize(Vector2 window_size);
				Vector2 getWindowSize();

				void maximizeWindow();
				bool getMaximized();

				GLFWwindow* getGLFWWindowPtr();
				GLFWmonitor* getGLFWMonitorPtr();

				Vector2 centreWindow();
				Vector2 centreWindow(GLFWmonitor* monitor);

				bool setVisibility(bool visible);
				bool getVisibility();

			};

			void init();
			void glfw_error_callback(int error, const char* error_desc);
			ALCB_Window CreateWindow(WindowInstance_CreationOptions start_opts);
			ALCB_Window CreateWindow();

			extern std::vector<internal_WindowInstance*> window_internal_instances_;
			extern int Window_count;

		}
	}
}