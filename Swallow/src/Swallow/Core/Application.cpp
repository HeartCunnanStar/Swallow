#include "swpch.h"
#include "Application.h"

#include "Swallow/Core/Log.h"
#include "Swallow/Core/Input.h"

#include "Swallow/Renderer/Renderer.h"
#include "Swallow/Renderer/RenderCommand.h"

#include <GLFW/glfw3.h>

namespace Swallow {

//there is no more need after we have define SW_BIND_EVENT_FN in core.h
//#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		SW_PROFILE_FUNCTION();

		SW_CORE_ASSERT(!s_instance, "Application instance already had one");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::CreateIns());
		m_window->SetEventCallback(SW_BIND_EVENT_FN(Application::OnEvent));
		//m_window->SetVSync(false);

		Renderer::Init();

		m_imgui_layer = new ImGuiLayer;
		PushOverlayer(m_imgui_layer);
	}

	Application::~Application()
	{
		SW_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		SW_PROFILE_FUNCTION();

		m_layer_stack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlayer(Layer* layer)
	{
		SW_PROFILE_FUNCTION();

		m_layer_stack.PushOverlayer(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& event)
	{
		SW_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(SW_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SW_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_layer_stack.end(); it != m_layer_stack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.is_handled)
				break;
		}
	}

	void Application::Run()
	{
		SW_PROFILE_FUNCTION();

		while (m_running)
		{		
			SW_PROFILE_SCOPE("App run loop -// void Application::Run()");

			// Temporary
			float time = glfwGetTime();
			TimeStep time_step = time - m_last_time;
			m_last_time = time;

			if (!m_minimized)
			{
				SW_PROFILE_SCOPE("LayerStack OnUpdate -// void Application::Run()");

				for (Layer* layer : m_layer_stack)
					layer->OnUpdate(time_step);
			}	

			m_imgui_layer->Begin();
			{
				SW_PROFILE_SCOPE("LayerStack OnImGuiUpdate -// void Application::Run()");

				for (Layer* layer : m_layer_stack)
					layer->OnImGuiRender();
			}
			m_imgui_layer->End();

			// for DEBUG
			//auto [x, y] = Input::GetMousePos();
			//SW_CORE_TRACE("{0}, {1}", x, y);

			m_window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		SW_PROFILE_FUNCTION();

		if (event.GetWidth() == 0 && event.GetHeight() == 0)
		{
			m_minimized = true;
			return false;
		}
		m_minimized = false;
		Renderer::OnWinodwResize(event.GetWidth(), event.GetHeight());
		return false;
	}

}