#include "window.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdlib.h>
#include <iostream>

namespace UILy
{
	Window::Window(WindowState state, bool decorated, const char* title, int width, int height)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_MAXIMIZED, (state == WindowState::MAXIMIZED)? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_DECORATED, decorated? GL_TRUE : GL_FALSE);

		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
		if(m_Window == NULL) {
			std::cerr << "Could not initialize window!" << std::endl;
			exit(-1);
		}
		glfwMakeContextCurrent(m_Window);
		m_Title = (char*) title;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		// From my testing KDE Plasma with X11 has issues with Viewports
		#ifndef __linux__
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		#endif

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
		}
		else
		{
			style.WindowRounding = 4.0f;
		}
		style.FrameRounding = 4.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		
		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	Window::~Window()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	bool Window::IsOpen()
	{
		return !glfwWindowShouldClose(m_Window);
	}

	void Window::Flip()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
		}
		glfwSwapBuffers(m_Window);
	}

	void Window::close()
	{
		glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
	}

	int Window::getInnerWidth()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		return io.DisplaySize.x;
	}

	int Window::getInnerHeight()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		return io.DisplaySize.y;
	}

	int Window::getX()
	{
		int x;
		glfwGetWindowPos(m_Window, &x, NULL);
		return x;
	}

	int Window::getY()
	{
		int y;
		glfwGetWindowPos(m_Window, NULL, &y);
		return y;
	}

	void Window::setPosition(int x, int y)
	{
		glfwSetWindowPos(m_Window, x, y);
	}

	const char* Window::getTitle()
	{
		return m_Title;
	}

	GLFWwindow* Window::getGLFWWindow()
	{
		return m_Window;
	}
} // namespace UILy
