#pragma once

#include "Core.h"

#include "Window.h"
#include "Swallow/LayerStack.h"
#include "Swallow/Events/Event.h"
#include "Swallow/Events/ApplicationEvent.h"

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
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layer_stack;
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}