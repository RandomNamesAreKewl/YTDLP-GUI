#pragma once
#include <imgui/imgui.h>
#include <vector>
#include <string>

namespace UILy
{
	enum DebugLevel
	{
		INFO,
		WARNING,
		ERROR
	};

	void showDebugConsole(bool* open);
	void debugLog(DebugLevel level, std::string msg);

#ifdef UILY_LIB
	std::vector<std::pair<DebugLevel, std::string>> g_DebugLog;
#endif
} // namespace UILy
