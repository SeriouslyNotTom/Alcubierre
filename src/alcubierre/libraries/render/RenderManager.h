#pragma once

#include <stdlib.h>
#include <functional>
#include <vector>

#include <Alcubierre/Libraries/Render/Window/WindowManager.h>

class Renderable
{
public:
	virtual void AcceptWindow(Window* window) {};
	virtual void Init() {};
	virtual void PreRender() {};
	virtual void Render() {};
	virtual void PostRender() {};
};

class RenderManager
{
public:
	void Add(Renderable* obj);
	void Render_HOOK();
	void Init();
	Window* myWindow;
private:
	std::vector<Renderable*> RenderOBJs_;
	void DoRenders_();
};