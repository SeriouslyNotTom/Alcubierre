#pragma once

#include <Alcubierre/Libraries/Render/RenderManager.h>
#include <Alcubierre/Libraries/Render/Window/WindowManager.h>

class ImGui_Render
{
public:
	virtual void ImGuiFrameStart() {};
	virtual void ImGuiFrameEnd() {};
};

class ImGui_Handler : public Renderable
{
private:
	std::vector<ImGui_Render*> ImGuiObjs;
	Window* window_;
	void ImGui_Frame_Start();
	void ImGui_Frame_End();
public:
	void AcceptWindow(Window* window);
	void ApplyColors();
	void ApplyStyles();
	void Init();
	void Render();
	const typedef void (*FrameStartCB)();
	std::vector<void(*)()> frame_start_callbacks_;
	void AddFrameStart(void(*cbf)());
	void AddImGuiRenderableOBJ(ImGui_Render* obj);
};