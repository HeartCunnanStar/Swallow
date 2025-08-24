#include "swpch.h"
#include "WindowsInput.h"

#include "GLFW/glfw3.h"
#include "Swallow/Application.h"

namespace Swallow{

	Input* Input::s_instance = new WindowsInput();

	bool WindowsInput::IsKeyDownImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonDownImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
		double pos_x, pos_y;
		glfwGetCursorPos(window, &pos_x, &pos_y);

		return std::pair<float, float>(static_cast<float>(pos_x), static_cast<float>(pos_y));
	}

	float WindowsInput::GetMouseXImpl()
	{
		// before c17
		//auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
		//double pos_x, pos_y;
		//glfwGetCursorPos(window, &pos_x, &pos_y);
		
		// after c17
		auto [pos_x, pos_y] = GetMousePosImpl();

		return static_cast<float>(pos_x);
	}

	float WindowsInput::GetMouseYImpl()
	{
		// before c17
		//auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
		//double pos_x, pos_y;
		//glfwGetCursorPos(window, &pos_x, &pos_y);

		// after c17
		auto [pos_x, pos_y] = GetMousePosImpl();

		return static_cast<float>(pos_y);
	}
}


