#include <alcubierre/libraries/debug/Console.h>

#include <imgui.h>

void Console::Render()
{
	ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Console", NULL, ImGuiWindowFlags_NoCollapse))
	{
		ImGui::End();
		return;
	}

	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.30f, 0.09f, 0.39f, 0.39f));
	//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4,4));
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

	// Command-line
	bool reclaim_focus = false;
	ImGui::PushItemWidth(ImGui::GetWindowWidth() - 50);
	ImGui::InputText("", inputbuff, IM_ARRAYSIZE(inputbuff), ImGuiInputTextFlags_EnterReturnsTrue);
	ImGui::SameLine(ImGui::GetWindowWidth() - 40);
	ImGui::AlignTextToFramePadding();
	ImGui::Button("doit");
	// Auto-focus on window apparition
	ImGui::SetItemDefaultFocus();
	if (reclaim_focus)
		ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

	ImGui::End();
}

void Console::Init()
{
	lol.push_back("lol");
	lol.push_back("more stuff");
	memset(inputbuff, 0, sizeof(inputbuff));
}