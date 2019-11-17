#pragma once

#include <Alcubierre/Libraries/Debug/Debug_interface.h>
#include <vector>

class Test_Program
{
public:
	virtual bool* getEnableStatusPTR() { return NULL; };
	virtual void performRender() {};
	virtual char* getTestName() { return "untitled"; };
};

class TestProgram_handler : public ImGui_Render, public Debug_Menu, public Renderable
{
	std::vector<Test_Program*> TestPrograms_;
	std::vector<ImGui_Render*> TestPrograms_ImGui_;
	std::unordered_map<Test_Program*, bool*> EnabledStatus;
public:
	void ImGuiFrameStart();
	void TestMenuStart();
	void Init();
	void Render();
	void AddProgram(Test_Program* program);
	void AddProgramImGui(ImGui_Render* program);
};