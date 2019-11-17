#include <Alcubierre/Libraries/Render/RenderManager.h>

void RenderManager::Add(Renderable* obj)
{
	RenderOBJs_.push_back(obj);
}

void RenderManager::DoRenders_()
{
	for (Renderable*& OBJ : RenderOBJs_) {
		OBJ->Render();
	}
}

void RenderManager::Init()
{
	for (Renderable*& OBJ : RenderOBJs_)
	{
		OBJ->AcceptWindow(myWindow);
		OBJ->Init();
	}
}

void RenderManager::Render_HOOK()
{
	this->DoRenders_();
}