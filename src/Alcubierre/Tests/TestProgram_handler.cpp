#include <Alcubierre/Tests/TestProgram_handler.h>
#include <ImGui.h>
#include <glad/glad.h>

void TestProgram_handler::ImGuiFrameStart()
{
	for each (ImGui_Render* obj in this->TestPrograms_ImGui_)
	{
		obj->ImGuiFrameStart();
		obj->ImGuiFrameEnd();
	}
}

void TestProgram_handler::TestMenuStart()
{
	if (ImGui::BeginMenu("Demo Programs"))
	{
		ImGui::TextColored(ImVec4(255, 0, 0, 255), "Placeholder Text");
		for each (Test_Program* prg in TestPrograms_)
		{
			ImGui::Checkbox(prg->getTestName(), this->EnabledStatus[prg]);
			//fprintf(stdout, "DEBUG TESTMENU ITEM : %s\n", prg->getTestName());
		}
		ImGui::EndMenu();
	}
	
}

void TestProgram_handler::Init()
{
	this->EnabledStatus = std::unordered_map<Test_Program*, bool*>();
	fprintf(stdout, "fluff");
	//debug here, disapears here
	for each (Test_Program* obj in TestPrograms_)
	{
		this->EnabledStatus[obj] = obj->getEnableStatusPTR();
	}
}

void TestProgram_handler::Render()
{
	for each (Test_Program* prg in TestPrograms_)
	{
		if (this->EnabledStatus[prg]) { prg->performRender(); }
	}
}

void TestProgram_handler::AddProgram(Test_Program* program)
{
	this->TestPrograms_.push_back(program);
}

void TestProgram_handler::AddProgramImGui(ImGui_Render* obj)
{
	this->TestPrograms_ImGui_.push_back(obj);
}