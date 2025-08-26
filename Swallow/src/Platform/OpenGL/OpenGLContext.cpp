#include "swpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Swallow {

	OpenGLContext::OpenGLContext(GLFWwindow* window_handle)
		: m_window_handle(window_handle)
	{
		SW_CORE_ASSERT(window_handle, "window handle has wrongs!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_window_handle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SW_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_window_handle);
	}
}