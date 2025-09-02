#include "swpch.h"

#include "ImGuiLayer.h"

#include "imgui.h"

#define IMGUI_IMPL_API
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Swallow/Core/Application.h"

// TEMPORARY
#include "GLFW/glfw3.h"
#include "glad/glad.h"


namespace Swallow {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		SW_PROFILE_FUNCTION();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.f;
			style.Colors[ImGuiCol_WindowBg].w = 1.f;
		}
		Application& app = Application::GetIns();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

		// before 250823
		//ImGui::CreateContext();
		//ImGui::StyleColorsDark();

		//ImGuiIO& io = ImGui::GetIO();
		//io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		//io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//// TEMPORARY: should eventually use Hazel key codes
		//io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		//io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		//io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		//io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		//io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		//io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		//io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		//io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		//io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		//io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		//io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		//io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		//io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		//io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		//io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		//io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		//io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		//io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		//io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		//io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		//io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		//ImGui_ImplOpenGL3_Init("#version 410");
	}

	//void ImGuiLayer::OnImGuiRender()
	//{
	//	static bool show = true;
	//	ImGui::ShowDemoWindow(&show);
	//}

	void ImGuiLayer::OnDetach()
	{
		SW_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		SW_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		SW_PROFILE_FUNCTION();

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetIns();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	//	 before 250823
	//void ImGuiLayer::OnUpdate()
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	Application& app = Application::GetIns();
	//	io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

	//	float time = (float)glfwGetTime();
	//	io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
	//	m_time = time;

	//	ImGui_ImplOpenGL3_NewFrame();
	//	ImGui::NewFrame();

	//	static bool show = true;
	//	ImGui::ShowDemoWindow(&show);

	//	ImGui::Render();
	//	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//}

	// before 250823
	//void ImGuiLayer::OnEvent(Event& event)
	//{
	//	EventDispatcher dispather(event);
	//	dispather.Dispatch<MouseButtonDownEvent>(SW_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonDownEvent));
	//	dispather.Dispatch<MouseButtonUpEvent>(SW_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonUpEvent));
	//	dispather.Dispatch<MouseMovedEvent>(SW_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
	//	dispather.Dispatch<MouseScrolledEvent>(SW_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
	//	dispather.Dispatch<KeyTypedEvent>(SW_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
	//	dispather.Dispatch<KeyDownEvent>(SW_BIND_EVENT_FN(ImGuiLayer::OnKeyDownEvent));
	//	dispather.Dispatch<KeyUpEvent>(SW_BIND_EVENT_FN(ImGuiLayer::OnKeyUpEvent));
	//	dispather.Dispatch<WindowResizeEvent>(SW_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	//}

	//bool ImGuiLayer::OnMouseButtonDownEvent(MouseButtonDownEvent& event)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.MouseDown[event.GetMouseButton()] = true;

	//	return false;
	//}

	//bool ImGuiLayer::OnMouseButtonUpEvent(MouseButtonUpEvent& event)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.MouseDown[event.GetMouseButton()] = false;

	//	return false;
	//}

	//bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.MouseWheelH += event.GetXOffset();
	//	io.MouseWheel += event.GetYOffset();

	//	return false;
	//}

	//bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& event)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.MousePos = ImVec2(event.GetX(), event.GetY());

	//	return false;
	//}

	//bool ImGuiLayer::OnKeyDownEvent(KeyDownEvent& event)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.KeysDown[event.GetKeyCode()] = true;

	//	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	//	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	//	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	//	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	//	return false;
	//}

	//bool ImGuiLayer::OnKeyUpEvent(KeyUpEvent& event)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.KeysDown[event.GetKeyCode()] = false;

	//	return false;
	//}

	//bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& event)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	int key_code = event.GetKeyCode();
	//	if (key_code > 0 && key_code < 0x10000)
	//		io.AddInputCharacter((unsigned short)key_code);

	//	return false;
	//}

	//bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
	//	io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
	//	glViewport(0, 0, event.GetWidth(), event.GetHeight());

	//	return false;
	//}

}