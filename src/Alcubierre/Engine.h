#pragma once

#include <Alcubierre/Alcubierre.h>
#include <Alcubierre/Debug/Log.h>

#include <stdlib.h>
#include <unordered_map>

namespace Alcubierre
{
	namespace Engine
	{
		void Initialize();
		extern Window* _PrimaryWindow;
		void SpawnWindow(WindowManager::WindowCreationCallback* NewWindowCallback);
		void SetupContext();
	}

	namespace Renderer
	{

		class IRenderable
		{
			virtual bool PreRender() {};
			virtual bool OnRender() {};
			virtual bool PostRender() {};
		};

		class RenderQueueOBJ
		{
			IRenderable* IOBJ;
			IRenderable PreRenderHook[];
		};

		extern std::unordered_map<char*, RenderQueueOBJ> *RenderQueue;

		bool Initialize();
		void AddToQueue(IRenderable RenderableOBJ);
	}

	//namespace Window
	//{

	//}

}