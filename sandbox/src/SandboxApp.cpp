#include <Swallow.h>

class ExampleLayer : public Swallow::Layer
{
public:
	ExampleLayer() : Layer("Layer"), m_camera({ -1.6f, 1.6f, -0.9f, 0.9f }), m_camera_position(0.0f)
	{
		m_vertex_array.reset(Swallow::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.1f, 0.2f, 1.0f, 1.0f,
			 0.0f,  0.366f, 0.0f, 1.0f, 1.0f, 0.1f, 1.0f
		};
		std::shared_ptr<Swallow::VertexBuffer> vertex_buffer;
		vertex_buffer.reset(Swallow::VertexBuffer::Create(vertices, sizeof(vertices)));

		Swallow::BufferLayout layout = {
			{ Swallow::ShaderDataType::Float3, "a_Position" },
			{ Swallow::ShaderDataType::Float4, "a_Color" }
		};

		vertex_buffer->SetLayout(layout);
		m_vertex_array->AddVertexBuffer(vertex_buffer);

		unsigned int indicies[3] = { 0, 1, 2 };
		std::shared_ptr<Swallow::IndexBuffer> index_buffer;
		index_buffer.reset(Swallow::IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t)));
		m_vertex_array->SetIndexBuffer(index_buffer);

		// -----try to draw a square---------------
		m_squareVA.reset(Swallow::VertexArray::Create());
		float sqaure_vertices[3 * 4] = {
		   -0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f,  0.75f, 0.0f,
		   -0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<Swallow::VertexBuffer> squareVB;
		squareVB.reset(Swallow::VertexBuffer::Create(sqaure_vertices, sizeof(sqaure_vertices)));

		Swallow::BufferLayout square_layout = {
			{ Swallow::ShaderDataType::Float3, "a_Position" }
		};

		squareVB->SetLayout(square_layout);
		m_squareVA->AddVertexBuffer(squareVB);

		unsigned int square_indicies[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Swallow::IndexBuffer> squareIB;
		squareIB.reset(Swallow::IndexBuffer::Create(square_indicies, sizeof(square_indicies) / sizeof(uint32_t)));
		m_squareVA->SetIndexBuffer(squareIB);

		// -----------write shaders-------------------
		std::string vertex_src = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_shader.reset(new Swallow::Shader(vertex_src, fragment_src));
		m_shader2.reset(new Swallow::Shader(square_vertex_src, square_fragment_src));
	}

	void OnUpdate(Swallow::TimeStep time_step) override
	{
		//SW_TRACE("Delta time : {0}s", time_step.GetSeconds());

		if (Swallow::Input::IsKeyDown(SW_KEY_LEFT))
			m_camera_position.x -= m_camera_speed * time_step;
		else if (Swallow::Input::IsKeyDown(SW_KEY_RIGHT))
			m_camera_position.x += m_camera_speed * time_step;

		if (Swallow::Input::IsKeyDown(SW_KEY_DOWN))
			m_camera_position.y -= m_camera_speed * time_step;
		else if (Swallow::Input::IsKeyDown(SW_KEY_UP))
			m_camera_position.y += m_camera_speed * time_step;

		if (Swallow::Input::IsKeyDown(SW_KEY_R))
			m_camera_rotation += m_camera_rotation_speed * time_step;

		Swallow::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Swallow::RenderCommand::Clear();

		m_camera.SetPosition(m_camera_position);
		m_camera.SetRotation(m_camera_rotation);

		Swallow::Renderer::BeginScene(m_camera);

		Swallow::Renderer::Submit(m_squareVA, m_shader2);
		Swallow::Renderer::Submit(m_vertex_array, m_shader);

		Swallow::Renderer::EndScene();

		// SW for DEBUG
		//SW_INFO("ExampleLayer::Update");
		// SW for DEBUG
		//if (Swallow::Input::IsKeyDown(SW_KEY_TAB))
		//	SW_TRACE("Key TAB is down (poll)");
	}

	void OnEvent(Swallow::Event& event)  override
	{
				// SW for DEBUG
				//SW_TRACE("{0}", event.ToString());
				// SW for DEBUG
				//if (event.GetEventType() == Swallow::EventType::KeyDown)
				//{
				//	Swallow::KeyDownEvent& e = static_cast<Swallow::KeyDownEvent&>(event);
				//	if (e.GetKeyCode() == SW_KEY_TAB)
				//		SW_TRACE("Key TAB is down (event)");
				//	else
				//		SW_TRACE("{0}", static_cast<char>(e.GetKeyCode()));
				//	
				//}
	}

private:
	// fro DEBUG : triangle
	std::shared_ptr<Swallow::VertexArray> m_vertex_array;
	std::shared_ptr<Swallow::Shader> m_shader;

	// for DEBUG : square
	std::shared_ptr<Swallow::Shader> m_shader2;
	std::shared_ptr<Swallow::VertexArray> m_squareVA;

	Swallow::OrthographicCamera m_camera;

	glm::vec3 m_camera_position;
	float m_camera_speed = 1.0f;

	float m_camera_rotation_speed = 10.0f;
	float m_camera_rotation = 0.0f;
};

class Sandbox : public Swallow::Application
{
public: 
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushLayer(new Swallow::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Swallow::Application* Swallow::CreateApplication()
{
	return new Sandbox();
}