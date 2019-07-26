#include <alcubierre/libraries/debug/Console.h>

#include <imgui.h>

void Console::Render()
{
	if (!ShouldDraw) return;
	ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Console", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar))
	{
		ImGui::End();
		return;
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::Text("lol");
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.30f, 0.09f, 0.39f, 0.39f));
	//ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
	if (ImGui::BeginPopupContextWindow())
	{
		//if (ImGui::Selectable("Clear")) ClearLog();
		ImGui::EndPopup();
	}
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
	for (int i = 0; i < lol.size(); i++)
	{
		const char* item = lol[i];

		// Normally you would store more information in your item (e.g. make Items[] an array of structure, store color/type etc.)
		bool pop_color = false;
		if (strstr(item, "[error]")) { ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f)); pop_color = true; }
		else if (strncmp(item, "# ", 2) == 0) { ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.6f, 1.0f)); pop_color = true; }
		ImGui::TextUnformatted(item);
		if (pop_color)
			ImGui::PopStyleColor();
	}
	//if (ScrollToBottom)
		//ImGui::SetScrollHereY(1.0f);
	//ScrollToBottom = false;
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::EndChild();

	ImGui::Separator();
	// Command-line
	bool reclaim_focus = false;
	ImGui::PushItemWidth(ImGui::GetWindowWidth() - 10);
	ImGui::InputText("", inputbuff, IM_ARRAYSIZE(inputbuff), ImGuiInputTextFlags_EnterReturnsTrue);
	ImGui::SameLine(ImGui::GetWindowWidth() - 40*2);
	ImGui::AlignTextToFramePadding();
	// Auto-focus on window apparition
	ImGui::SetItemDefaultFocus();
	if (reclaim_focus)
		ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

	ImGui::End();
}

void Console::Init()
{
	inputbuff = new char[1024];
	lol.push_back("lol");
	lol.push_back("more stuff");
	memset(inputbuff, 0, sizeof(inputbuff));
}