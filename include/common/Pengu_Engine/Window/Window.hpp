#ifndef WINDOW_HPP
#define WINDOW_HPP 1


#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>
#include <optional>

class Window {
public:
	Window(int width, int height, const std::string& name);

	Window(const Window& rvalue) = delete;
	Window& operator = (const Window& rvalue) = delete;

	Window(Window&& rvalue) noexcept : window_(rvalue.window_)
	{
		rvalue.window_ = nullptr;
	};
	Window& operator = (Window&& rvalue) noexcept
	{
		if (this != &rvalue)
		{
			// Clean up existing resource
			if (window_)
			{
				glfwDestroyWindow(window_);
			}

			// Transfer ownership
			window_ = rvalue.window_;

			// Leave source in valid empty state
			rvalue.window_ = nullptr;
		}

		return *this;
	};

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	int GetWidth();
	int GetHeight();

	GLFWwindow* GetWindow() const;

	~Window();

private:
	GLFWwindow* window_;
};

#endif // !__WINDOW_HPP__ 1


