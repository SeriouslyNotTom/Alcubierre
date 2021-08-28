#include <Alcubierre/Alcubierre.h>

namespace Alcubierre
{
	namespace Engine
	{
		namespace Window
		{
			class WindowInstance
			{
			public:
				GLFWmonitor* glfw_monitor;
				GLFWwindow* glfw_window;
				GLFWwindow* glfw_share_window;
				int window_width, window_height;
				char* window_title;
				void CenterWindow();
				void CenterWindow(GLFWmonitor* monitor);
			};

			const typedef std::function<void(WindowInstance*)> WindowCreationCallback;
			static WindowInstance* createWindow(WindowCreationCallback* window_cb);
		}
	}
}