#include <GLFW/glfw3.h>

namespace UILy
{
	enum class WindowState
	{
		WINDOWED,
		MAXIMIZED
	};

	/// @brief A class for keeping track of a UILy window
	class Window
	{
	public:
		Window(WindowState state, bool decorated=true, const char* title="UILy Window", int width=1280, int height=720);
		~Window();

		/// @brief Checks if the window should still be open.
		/// @return Whether should the window be open
		bool IsOpen();

		/// @brief Updates the window's context to what has been rendered in the current frame
		void Flip();

		int getInnerWidth();
		int getInnerHeight();

		int getX();
		int getY();

		void close();

		void setPosition(int x, int y);

		const char* getTitle();
		GLFWwindow* getGLFWWindow();

	private:
		char* m_Title;
		GLFWwindow* m_Window;
	};
} // namespace UILy

