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
		SW_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_window_handle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SW_CORE_ASSERT(status, "Failed to initialize Glad!");

		SW_CORE_INFO("OpenGL infomation:");
		SW_CORE_INFO("|-Vendor:   {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		SW_CORE_INFO("|-Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		SW_CORE_INFO("|-Verion:   {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffers()
	{
		SW_PROFILE_FUNCTION();

		glfwSwapBuffers(m_window_handle);
	}
}