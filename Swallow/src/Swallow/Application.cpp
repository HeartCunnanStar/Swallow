#include "swpch.h"
#include "Application.h"

#include "Swallow/Log.h"

#include <glad/glad.h>

#include "Swallow/Input.h"

namespace Swallow {

//there is no more need after we have define SW_BIND_EVENT_FN in core.h
//#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)

	Application* Application::s_instance = nullptr;

	static GLenum ShaderDataType2OpenGLType(ShaderDataType type)
	{
		using SD = ShaderDataType;
		switch (type)
		{
		case SD::Bool:		return GL_BOOL;
		case SD::Float:
		case SD::Float2:
		case SD::Float3:
		case SD::Float4:	return GL_FLOAT;
		case SD::Int:		
		case SD::Int2:		
		case SD::Int3:		
		case SD::Int4:		return GL_INT;
		case SD::Mat3:
		case SD::Mat4:		return GL_FLOAT;
		}

		SW_CORE_ASSERT(false, "Unknow ShaderDataType!");
		return 0;
	}

	Application::Application()
	{
		SW_CORE_ASSERT(!s_instance, "Application instance already had one");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(SW_BIND_EVENT_FN(Application::OnEvent));

		m_imgui_layer = new ImGuiLayer;
		PushOverlayer(m_imgui_layer);

		glGenVertexArrays(1, &m_vertex_array);
		glBindVertexArray(m_vertex_array);

		// for DEBUG
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		m_vertex_buffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" }
		};
		
		uint32_t index = 0;
		for (const auto& ele : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, ele.GetComponentCount(), 
				ShaderDataType2OpenGLType(ele.type), 
				ele.is_normalized ? GL_TRUE : GL_TRUE,
				layout.GetStride(), 
				reinterpret_cast<const void*>(ele.offset));
			++index;
		}

		unsigned int indicies[3] = { 0, 1, 2 };
		m_index_buffer.reset(IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t)));

		std::string vertex_src = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;  

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}	
		)";

		std::string fragment_src = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}	
		)";

		m_shader.reset(new Shader(vertex_src, fragment_src));
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

			m_shader->Bind();

			glBindVertexArray(m_vertex_array);
			glDrawElements(GL_TRIANGLES, m_index_buffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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