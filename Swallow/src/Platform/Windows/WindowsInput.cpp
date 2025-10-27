#include "swpch.h"
#include "Swallow/Core/Input.h"

#include "GLFW/glfw3.h"
#include "Swallow/Core/Application.h"

namespace Swallow{

	bool Input::IsKeyDown(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonDown(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePos()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
		double pos_x, pos_y;
		glfwGetCursorPos(window, &pos_x, &pos_y);

		return std::pair<float, float>(static_cast<float>(pos_x), static_cast<float>(pos_y));
	}

	float Input::GetMouseX()
	{
		auto [pos_x, pos_y] = GetMousePos();

		return static_cast<float>(pos_x);
	}

	float Input::GetMouseY()
	{
		auto [pos_x, pos_y] = GetMousePos();

		return static_cast<float>(pos_y);
	}
	//Input* Input::s_instance = new Input();
	//bool Input::IsKeyDownImpl(int keycode)
	//{
	//	auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
	//	auto state = glfwGetKey(window, keycode);
	//	return state == GLFW_PRESS || state == GLFW_REPEAT;
	//}
	//bool Input::IsMouseButtonDownImpl(int button)
	//{
	//	auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
	//	auto state = glfwGetMouseButton(window, button);
	//	return state == GLFW_PRESS;
	//}
	//std::pair<float, float> Input::GetMousePosImpl()
	//{
	//	auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
	//	double pos_x, pos_y;
	//	glfwGetCursorPos(window, &pos_x, &pos_y);
	//	return std::pair<float, float>(static_cast<float>(pos_x), static_cast<float>(pos_y));
	//}
	//float Input::GetMouseXImpl()
	//{
	//	// before c17
	//	//auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
	//	//double pos_x, pos_y;
	//	//glfwGetCursorPos(window, &pos_x, &pos_y);
	//	
	//	// after c17
	//	auto [pos_x, pos_y] = GetMousePosImpl();
	//	return static_cast<float>(pos_x);
	//}
	//float Input::GetMouseYImpl()
	//{
	//	// before c17
	//	//auto window = static_cast<GLFWwindow*>(Application::GetIns().GetWindow().GetNativeWindow());
	//	//double pos_x, pos_y;
	//	//glfwGetCursorPos(window, &pos_x, &pos_y);
	//	// after c17
	//	auto [pos_x, pos_y] = GetMousePosImpl();
	//	return static_cast<float>(pos_y);
	//}

}