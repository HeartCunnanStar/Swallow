#pragma once

#include "Core.h"

#include "Window.h"
#include "Swallow/LayerStack.h"
#include "Swallow/Events/Event.h"
#include "Swallow/Events/ApplicationEvent.h"
#include "Swallow/ImGui/ImGuiLayer.h"

// FOR DEBUG
#include "Swallow/Renderer/Shader.h"
#include "Swallow/Renderer/Buffer.h"

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

		ImGuiLayer* m_imgui_layer;
		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layer_stack;

		unsigned int m_vertex_array;
		std::unique_ptr<VertexBuffer> m_vertex_buffer;
		std::unique_ptr<IndexBuffer> m_index_buffer;

		// FOR DEBUG
		std::unique_ptr<Shader> m_shader;

		static Application* s_instance;
	};

	// to be defined in CLIENT
	Application* CreateApplication();
}