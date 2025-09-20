#pragma once

#include "Core.h"

#include "Window.h"
#include "Swallow/Core/LayerStack.h"
#include "Swallow/Events/Event.h"
#include "Swallow/Events/ApplicationEvent.h"
#include "Swallow/ImGui/ImGuiLayer.h"
#include "Swallow/Core/TimeStep.h"

#include <memory>

namespace Swallow {

	class SWALLOW_API Application
	{
	public:
		Application(const std::string& name = "Swallow App");
		virtual ~Application();

		void Run();
		void Close();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlayer(Layer* layer);

		inline Window& GetWindow() { return *m_window; }
		inline ImGuiLayer* GetImGuiLayer() { return m_imgui_layer; }

		inline static Application& GetIns() { return *s_instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

	private:
		ImGuiLayer* m_imgui_layer;
		std::unique_ptr<Window> m_window;
		bool m_running = true;
		bool m_minimized = false;

		LayerStack m_layer_stack;
		TimeStep m_time_step;
		float m_last_time;

		static Application* s_instance;
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}