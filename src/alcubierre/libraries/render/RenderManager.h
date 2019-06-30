#include <cppc/render/window_manager.cpp>

class RenderManager
{
public:
	static void DoRenders();
};

class Renderable
{
public:
	//apparently i need a default definition for virtual functions
	virtual void AcceptWindow(Window* window) {};
	virtual void Init() {};
	virtual void PreRender() {};
	virtual void Render() {};
	virtual void PostRender() {};
};