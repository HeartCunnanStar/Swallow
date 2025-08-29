#pragma once

#include "Core.h"

#include "Window.h"
#include "Swallow/LayerStack.h"
#include "Swallow/Events/Event.h"
#include "Swallow/Events/ApplicationEvent.h"
#include "Swallow/ImGui/ImGuiLayer.h"
#include "Swallow/Core/TimeStep.h"

#include <memory>

namespace Swallow {

	class SWALLOW_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlayer(Layer* layer);

		inline Window& GetWindow() { return *m_window; }

		inline static Application& GetIns() { return *s_instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);

	private:
		ImGuiLayer* m_imgui_layer;
		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layer_stack;
		TimeStep m_time_step;
		float m_last_time;

		static Application* s_instance;
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}