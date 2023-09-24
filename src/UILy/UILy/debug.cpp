#define UILY_LIB
#include "debug.h"

namespace UILy
{
	char g_DebugConsoleFilter[128];
	void showDebugConsole(bool *open=NULL)
	{
		ImGui::SetNextWindowSize({640, 480}, ImGuiCond_FirstUseEver);
		if(ImGui::Begin("Debug Console", open))
		{
			if(ImGui::Button("Clear"))
			{
				g_DebugLog.clear();
			}
			ImGui::SameLine();
			ImGui::InputText("Filter", g_DebugConsoleFilter, 128);
			static bool showInfo = true;
			static bool showWarnings = true;
			static bool showErrors = true;
			ImGui::SameLine();
			ImGui::Checkbox("Info", &showInfo);
			ImGui::SameLine();
			ImGui::Checkbox("Warn", &showWarnings);
			ImGui::SameLine();
			ImGui::Checkbox("Error", &showErrors);
			ImGui::Separator();
			if(ImGui::BeginChild(ImGui::GetID("ConsoleLog"))) {
				for (size_t i = 0; i < g_DebugLog.size(); i++)
				{
					if(g_DebugLog[i].second.find(g_DebugConsoleFilter) == std::string::npos)
						continue;
					switch (g_DebugLog[i].first)
					{
					case DebugLevel::INFO:
						if(!showInfo)
							break;
						ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1), "[INFO] %s", g_DebugLog[i].second.c_str());
						break;

					case DebugLevel::WARNING:
						if(!showWarnings)
							break;
						ImGui::TextColored(ImVec4(1, 1, 0, 1), "[WARNING] %s", g_DebugLog[i].second.c_str());
						break;

					case DebugLevel::ERROR:
						if(!showErrors)
							break;
						ImGui::TextColored(ImVec4(1, 0, 0, 1), "[ERROR] %s", g_DebugLog[i].second.c_str());
						break;
					
					default:
						ImGui::TextColored(ImVec4(1, 1, 1, 1), "%s", g_DebugLog[i].second.c_str());
						break;
					}
				}
				ImGui::EndChild();
			}
			
			ImGui::End();
		}
	}

	void debugLog(DebugLevel level, std::string msg)
	{
		UILy::g_DebugLog.push_back({level, msg});
	}
} // namespace UILy
