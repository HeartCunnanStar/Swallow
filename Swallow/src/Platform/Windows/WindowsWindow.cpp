#include "swpch.h"
#include "WindowsWindow.h"

#include "Swallow/Events/ApplicationEvent.h"
#include "Swallow/Events/MouseEvent.h"
#include "Swallow/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Swallow {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		SW_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::CreateIns(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		SW_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		SW_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		SW_PROFILE_FUNCTION();

		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		SW_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!s_GLFWInitialized)
		{
			SW_PROFILE_SCOPE("glfwInit -// void WindowsWindow::Init(const WindowProps&)");

			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			SW_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		{
			SW_PROFILE_SCOPE("glfwCreateWindow -// void WindowsWindow::Init(const WindowProps&)");
			m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
		}

		m_context = GraphicsContext::CreateIns(m_window);
		m_context->Init();

		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.event_callback(event);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.event_callback(event);
			});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyDownEvent event(key, 0);
					data.event_callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyUpEvent event(key);
					data.event_callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyDownEvent event(key, 1);
					data.event_callback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int key_code)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(key_code);
				data.event_callback(event);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonDownEvent event(button);
					data.event_callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonUpEvent event(button);
					data.event_callback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.event_callback(event);
			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double pos_x, double pos_y)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)pos_x, (float)pos_y);
				data.event_callback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		SW_PROFILE_FUNCTION();

		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::OnUpdate()
	{
		SW_PROFILE_FUNCTION();

		glfwPollEvents();
		m_context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool flag)
	{
		SW_PROFILE_FUNCTION();

		if (flag)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.is_vertical_sync = flag;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_data.is_vertical_sync;
	}

}