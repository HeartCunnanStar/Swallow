#include <Swallow.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

class ExampleLayer : public Swallow::Layer
{
public:
	ExampleLayer() : Layer("Layer"), m_camera({ -1.6f, 1.6f, -0.9f, 0.9f }), m_camera_position(0.0f),
		m_square_position(0.0f)
	{
		m_vertex_array = Swallow::VertexArray::CreateIns();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.1f, 0.2f, 1.0f, 1.0f,
			 0.0f,  0.366f, 0.0f, 1.0f, 1.0f, 0.1f, 1.0f
		};
		Swallow::Ref<Swallow::VertexBuffer> vertex_buffer;
		vertex_buffer.reset(Swallow::VertexBuffer::CreateIns(vertices, sizeof(vertices)));

		Swallow::BufferLayout layout = {
			{ Swallow::ShaderDataType::Float3, "a_Position" },
			{ Swallow::ShaderDataType::Float4, "a_Color" }
		};

		vertex_buffer->SetLayout(layout);
		m_vertex_array->AddVertexBuffer(vertex_buffer);

		unsigned int indicies[3] = { 0, 1, 2 };
		Swallow::Ref<Swallow::IndexBuffer> index_buffer;
		index_buffer.reset(Swallow::IndexBuffer::CreateIns(indicies, sizeof(indicies) / sizeof(uint32_t)));
		m_vertex_array->SetIndexBuffer(index_buffer);

		// -----try to draw a square---------------
		m_squareVA = Swallow::VertexArray::CreateIns();
		float sqaure_vertices[5 * 4] = {
		   -0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
		   -0.75f,  0.75f, 0.0f, 0.0f, 1.0f
		};

		Swallow::Ref<Swallow::VertexBuffer> squareVB;
		squareVB.reset(Swallow::VertexBuffer::CreateIns(sqaure_vertices, sizeof(sqaure_vertices)));

		// layout
		Swallow::BufferLayout square_layout = {
			{ Swallow::ShaderDataType::Float3, "a_Position" },
			{ Swallow::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(square_layout);
		m_squareVA->AddVertexBuffer(squareVB);

		unsigned int square_indicies[6] = { 0, 1, 2, 2, 3, 0 };
		Swallow::Ref<Swallow::IndexBuffer> squareIB;
		squareIB.reset(Swallow::IndexBuffer::CreateIns(square_indicies, sizeof(square_indicies) / sizeof(uint32_t)));
		m_squareVA->SetIndexBuffer(squareIB);

		//------------write shaders-------------------
		//-shader of triangle-------------------------
		std::string vertex_src = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_shader = Swallow::Shader::CreateIns(vertex_src, fragment_src);

		// shader of rectangle------------------------
		std::string square_vertex_src = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}	
		)";

		std::string square_fragment_src = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}	
		)";

		m_shader2 = Swallow::Shader::CreateIns(square_vertex_src, square_fragment_src);

		//-shader of texture---------------------------------
		std::string texture_vertex_src = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}	
		)";

		std::string texture_fragment_src = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}	
		)";

		//m_texture_shader = Swallow::Shader::CreateIns(texture_vertex_src, texture_fragment_src);

		m_texture_shader = Swallow::Shader::CreateIns("assets/shaders/Texture.glsl");

		std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_texture_shader)->Bind();
		std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_texture_shader)->UploadUniformInt("u_Texture", 0);

		m_texture = Swallow::Texture2D::CreateIns("assets/textures/kita_test.png");
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

		//------------------render--------------------
		Swallow::Renderer::BeginScene(m_camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.06f));

		std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_shader2)->Bind();
		std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_shader2)->UploadUniformFloat3("u_Color", m_square_color);

		for (int y = 0; y < 20; ++y)
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Swallow::Renderer::Submit(m_squareVA, m_shader2, transform);
			}
		
		m_texture->Bind();
		Swallow::Renderer::Submit(m_squareVA, m_texture_shader, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
		
		// Triangle
		//Swallow::Renderer::Submit(m_vertex_array, m_shader);

		Swallow::Renderer::EndScene();
		//---------------------------------------------------

		// SW for DEBUG
		//SW_INFO("ExampleLayer::Update");
		// SW for DEBUG
		//if (Swallow::Input::IsKeyDown(SW_KEY_TAB))
		//	SW_TRACE("Key TAB is down (poll)");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Sqaure color", glm::value_ptr(m_square_color));
		ImGui::End();
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
	Swallow::Ref<Swallow::VertexArray> m_vertex_array;
	Swallow::Ref<Swallow::Shader> m_shader;

	// for DEBUG : square
	Swallow::Ref<Swallow::Shader> m_shader2, m_texture_shader;
	Swallow::Ref<Swallow::VertexArray> m_squareVA;

	// for DEBUG : texture
	Swallow::Ref<Swallow::Texture2D> m_texture;

	Swallow::OrthographicCamera m_camera;

	glm::vec3 m_camera_position;
	float m_camera_speed = 1.0f;

	float m_camera_rotation_speed = 10.0f;
	float m_camera_rotation = 0.0f;

	glm::vec3 m_square_position;
	glm::vec3 m_square_color = { 0.2f, 0.3f, 0.8f };
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