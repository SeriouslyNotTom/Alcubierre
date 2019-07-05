#pragma once

#include <alcubierre/libraries/render/RenderManager.h>
#include <alcubierre/libraries/render/WindowManager.h>
#include <GLFW/glfw3.h>

class ImGui_Handler: public Renderable
{
private:
	Window* window_;
	void ImGui_Frame_Start();
	void ImGui_Frame_End();
public:
	void AcceptWindow(Window *window);
	void ApplyColors();
	void ApplyStyles();
	void Init();
	void Render();
	const typedef void (*FrameStartCB)();
	std::vector<void(*)()> frame_start_callbacks_;
	void AddFrameStart(void(*cbf)());
};