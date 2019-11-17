#pragma once

#include <Alcubierre/Tests/TestProgram_handler.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <main.h>
#include <imgui.h>


class Test1 : public Test_Program, public ImGui_Render
{
private:
	bool Enabled = false;
	bool initDone = false;

	float xPos = 0.0;
	float yPos = 0.0;

	float verts[9] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f };
	unsigned int VBO, VAO;

	double timeStart, timeEnd;

	void init()
	{
		if (!initDone)
		{
			glGenBuffers(1, &VBO);
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}
		initDone = true;
	}

public:
	char* getTestName() { return "Test 1"; }
	bool* getEnableStatusPTR() { return &Enabled; }

	void performRender()
	{
		if (initDone & Enabled)
		{
			glBindVertexArray(VAO);
			verts[0] = xPos + -0.5F;
			verts[1] = yPos + -0.5F;
			verts[3] = xPos;
			verts[4] = yPos + 0.5f;
			verts[6] = xPos + 0.5f;
			verts[7] = yPos + -0.5f;
			glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		else { init(); }
	}

	void ImGuiFrameStart()
	{
		if (Enabled)
		{
			if (ImGui::Begin("[Test1] Debug",&Enabled))
			{
				//ImGui::Text("Test 1 took %d ms", (float)(timeEnd - timeStart));
				ImGui::SliderFloat("xPos", &xPos, -1, 1);
				ImGui::SliderFloat("yPos", &yPos, -1, 1);
				ImGui::End();
			}
		}
	}
};


class Demos
{
	Test1 new_Test1;
public:
	void LoadTestPrograms()
	{
		new_Test1 = Test1();
		Alcubierre::Test_Programs.AddProgram(&new_Test1);
		Alcubierre::Test_Programs.AddProgramImGui(&new_Test1);
	}
};
