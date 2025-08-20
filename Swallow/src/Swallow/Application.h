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

		void run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}