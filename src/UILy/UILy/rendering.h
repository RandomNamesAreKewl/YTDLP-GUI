#pragma once
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <iostream>

namespace UILy
{
	void beginFrame();
	void endFrame();

	bool initGLFW();

	void glfw_error_callback(int error, const char* description);

	bool beginFullWindow(Window* window);
	void endFullWindow();
} // namespace UILy
