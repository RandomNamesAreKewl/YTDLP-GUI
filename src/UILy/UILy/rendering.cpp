#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "window.h"
#include "rendering.h"

namespace UILy
{
	void beginFrame()
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void endFrame()
	{
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	bool initGLFW()
	{
		glfwSetErrorCallback(UILy::glfw_error_callback);
		return glfwInit();
	}

	void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "GLFW Error %d: %s\n", error, description);
	}

	bool beginFullWindow(Window* window)
	{
		ImGui::SetNextWindowPos({0, 0});
		ImGui::SetNextWindowSize({(float) window->getInnerWidth(), (float) window->getInnerHeight()});
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		return ImGui::Begin(window->getTitle(), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus);
	}

	void endFullWindow()
	{
		ImGui::End();
		ImGui::PopStyleVar(2);
	}
} // namespace UILy

