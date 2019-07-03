#pragma once

#include <alcubierre/libraries/render/WindowManager.h>
#include <stdlib.h>
#include <functional>
#include <vector>

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

class RenderManager
{
public:
	void Add(Renderable* obj);
	void Render_HOOK();
	void Init();
	Window* mywindow;
private:
	std::vector<Renderable*> RenderOBJs_;
	void DoRenders_();
};