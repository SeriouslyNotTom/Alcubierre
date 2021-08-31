#include <Alcubierre/Alcubierre.h>
#include <Alcubierre/Libraries/Window.h>

int main(int argc, char* argv[])
{
	Alcubierre::Accept_Arguments(argc, *argv);
	Alcubierre::Initialize_Core();
	Alcubierre::Engine::Window::init();
	Alcubierre::Engine::Window::ALCB_Window newwindow = Alcubierre::Engine::Window::CreateWindow();
	GLFWwindow* windowptr = newwindow.getGLFWWindowPtr();

	while (true)
	{
		Alcubierre::update();
	}
}