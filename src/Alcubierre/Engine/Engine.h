#pragma once

#include <Alcubierre/Alcubierre.h>
#include <Alcubierre/Debug/Log.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <unordered_map>
#include <functional>
#include <vector>
#include <map>
#include <Alcubierre/Engine/Engine_types.h>
#include <Alcubierre/Libraries/Window.h>

namespace Alcubierre
{

	namespace Renderer
	{

		class IRenderable
		{
		public:
			virtual bool PreRender() { return false; };
			virtual bool OnRender() { return false; };
			virtual bool PostRender() { return false; };
		};

		class RenderQueueOBJ
		{
		public:
			IRenderable* IOBJ;
			std::vector<IRenderable*> PreRenderHook;
		};

		extern std::unordered_map<char*, RenderQueueOBJ*>* RenderQueue;
		extern std::vector<IRenderable*>* RenderPointerQueue;
		static bool ListDirty;

		bool Initialize();
		void RebuildList();
		void AddToQueue(IRenderable RenderableOBJ);
		void AddPreRenderHook(char* RendererName, RenderQueueOBJ* HookOBJ);
		void AddPreRenderHook(RenderQueueOBJ* Renderer, RenderQueueOBJ* HookOBJ);
	}

	class ALCB_SceneObject
	{
		ALCBE::Node_3DTransform transform;
	};

	class ALCB_Entity : ALCB_SceneObject
	{

	};

	class ALCB_Camera : ALCB_Entity
	{

	};

	class ALCB_StaticMesh : ALCB_SceneObject
	{

	};

	class ALCB_Scene
	{
	private:
		std::vector<ALCB_Camera> scene_cameras;
		std::vector<ALCB_StaticMesh> scene_static_meshes;
		std::vector<ALCB_Entity> scene_entities;
	};

	class ALCB_View
	{
	private:
		ALCB_Scene* view_ptrScene;
		ALCB_Camera* view_ptrPrimaryCam;

	};

	

	class ALCB_Scene_Collection
	{
		std::vector<ALCB_Scene> scenes;
		int getSceneCount();
		int getTotalScenesAdded();
		bool addScene(ALCB_Scene scene);
		bool removeScene(ALCB_Scene scene);
		ALCB_Scene* getScenes();
	};

	class ALCB_View_Collection
	{
		std::vector<ALCB_View> views;
		int getViewCount();
		int getTotalViewsAdded();
		bool addView(ALCB_View view);
		bool removeScene(ALCB_View view);
		ALCB_View* getViews();
	};

	class ALCB_TASK
	{
	public:

		enum TaskProperties
		{
			TaskProperties_None = 0,
			TaskProperties_PreLoad = 1 << 0,
			TaskProperties_Load = 1 << 1,
			TaskProperties_Start = 1 << 2,
			TaskProperties_Execute = 1 << 3,
			TaskProperties_Tick = 1 << 4,
			TaskProperties_End = 1 << 5,
			TaskProperties_Shutdown = 1 << 6
		};

		virtual int GetTaskID();
		virtual char* GetTaskName();
		virtual bool PreLoad();
		virtual bool Load();
		virtual bool Start();
		virtual bool Execute();
		virtual bool Tick();
		virtual bool End();
		virtual bool Shutdown();
		virtual TaskProperties GetTaskProperties();

	};

	class ALCB_Task_Manager
	{
	private:
		std::vector<ALCB_TASK*> tasks;
		std::map<int, ALCB_TASK*> tasks_by_id;
		std::map<char*, ALCB_TASK*> tasks_by_name;

	public:
		bool addTask(ALCB_TASK* task);
		bool addTask(ALCB_TASK* task, char* name);
		bool removeTask(ALCB_TASK* task);
		ALCB_TASK** getTasks();

		void PreLoad();
		void Load();
		void Start();
		void Tick();
		void End();
		void Shutdown();

	};

	class ALCB_Engine
	{
	private:
		std::vector<ALCB_Scene> engine_scenes;
		std::vector<ALCB_View> engine_views;
		std::vector<Engine::Window::WindowInstance> windows;
		Alcubierre::ALCB_Task_Manager taskman;

	public:
		bool addScene(ALCB_Scene* scene);
		bool removeScene(ALCB_Scene* scene);
		ALCB_Scene** getScenes();
		void init();
		void registerTask(ALCB_TASK* task);
		void tick();
	};

	namespace Engine
	{
		extern Alcubierre::ALCB_Engine* engine_core;
		
		void Initialize();
		extern Window::WindowInstance* PrimaryWindow;
		void SpawnWindow(Window::WindowCreationCallback* NewWindowCallback);
		void SetupContext();
		void Tick();

	}

	

}