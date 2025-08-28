#include "swpch.h"
#include "Application.h"

#include "Swallow/Log.h"

#include <glad/glad.h>

#include "Swallow/Input.h"

namespace Swallow {

//there is no more need after we have define SW_BIND_EVENT_FN in core.h
//#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		SW_CORE_ASSERT(!s_instance, "Application instance already had one");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(SW_BIND_EVENT_FN(Application::OnEvent));

		m_imgui_layer = new ImGuiLayer;
		PushOverlayer(m_imgui_layer);

		m_vertex_array.reset(VertexArray::Create());

		// for DEBUG
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.1f, 0.2f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.1f, 1.0f
		};
		std::shared_ptr<VertexBuffer> vertex_buffer;
		vertex_buffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		 
		vertex_buffer->SetLayout(layout);
		m_vertex_array->AddVertexBuffer(vertex_buffer);

		unsigned int indicies[3] = { 0, 1, 2 };		
		std::shared_ptr<IndexBuffer> index_buffer;
		index_buffer.reset(IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t)));
		m_vertex_array->SetIndexBuffer(index_buffer);

		// -----try to draw a square---------------
		m_squareVA.reset(VertexArray::Create());
		float sqaure_vertices[3 * 4] = {
		   -0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f,  0.75f, 0.0f,
		   -0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(sqaure_vertices, sizeof(sqaure_vertices)));

		BufferLayout square_layout = {
			{ ShaderDataType::Float3, "a_Position" }		
		};

		squareVB->SetLayout(square_layout);
		m_squareVA->AddVertexBuffer(squareVB);

		unsigned int square_indicies[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(square_indicies, sizeof(square_indicies) / sizeof(uint32_t)));
		m_squareVA->SetIndexBuffer(squareIB);

		// -----------write shaders-------------------
		std::string vertex_src = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}	
		)";

		std::string fragment_src = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}	
		)";

		std::string square_vertex_src = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}	
		)";

		std::string square_fragment_src = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}	
		)";

		m_shader.reset(new Shader(vertex_src, fragment_src));
		m_shader2.reset(new Shader(square_vertex_src, square_fragment_src));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layer_stack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlayer(Layer* layer)
	{
		m_layer_stack.PushOverlayer(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(SW_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_layer_stack.end(); it != m_layer_stack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.is_handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_shader2->Bind();
			m_squareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_squareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_shader->Bind();
			m_vertex_array->Bind();
			glDrawElements(GL_TRIANGLES, m_vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_layer_stack)
				layer->OnUpdate();

			m_imgui_layer->Begin();
			for (Layer* layer : m_layer_stack)
				layer->OnImGuiRender();
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

}