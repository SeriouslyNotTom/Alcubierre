#include <alcubierre/libraries/render/RenderManager.h>
#include <alcubierre/forensics/Logging.h>
#include <cppc/render/window_manager.cpp>


class TestClass : public Renderable {
public:
	void Render()
	{
		Logger::General("this is a virtual function from testclas");
	}

	void AcceptWindow(Window* window)
	{
		windowobj = window;
	}
private:
	Window* windowobj;
};

void RenderManager::DoRenders()
{
	TestClass tc = TestClass();
	Renderable* renptr = &tc;
	renptr->Render();
	bool is = dynamic_cast<Renderable*>(&tc);
	bool ije = true;
}