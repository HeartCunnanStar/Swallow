#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_camera_controller(1280.f / 720.f)
{

}

void Sandbox2D::OnAttach()
{
	m_test_texture = Swallow::Texture2D::CreateIns("assets/textures/kita_test.png");

	//m_squareVA = Swallow::VertexArray::CreateIns();
	//float sqaure_vertices[5 * 4] = {
	//   -0.75f, -0.75f, 0.0f,
	//	0.75f, -0.75f, 0.0f,
	//	0.75f,  0.75f, 0.0f,
	//   -0.75f,  0.75f, 0.0f
	//};

	//Swallow::Ref<Swallow::VertexBuffer> squareVB;
	//squareVB.reset(Swallow::VertexBuffer::CreateIns(sqaure_vertices, sizeof(sqaure_vertices)));

	//// layout
	//Swallow::BufferLayout square_layout = {
	//	{ Swallow::ShaderDataType::Float3, "a_Position" }
	//};

	//squareVB->SetLayout(square_layout);
	//m_squareVA->AddVertexBuffer(squareVB);

	//unsigned int square_indicies[6] = { 0, 1, 2, 2, 3, 0 };
	//Swallow::Ref<Swallow::IndexBuffer> squareIB;
	//squareIB.reset(Swallow::IndexBuffer::CreateIns(square_indicies, sizeof(square_indicies) / sizeof(uint32_t)));
	//m_squareVA->SetIndexBuffer(squareIB);

	//m_shader = Swallow::Shader::CreateIns("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Swallow::TimeStep time_step)
{
	//--------------Updata-------------------
	m_camera_controller.OnUpdata(time_step);

	//--------------Render-------------------
	Swallow::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Swallow::RenderCommand::Clear();

	Swallow::Renderer2D::BeginScene(m_camera_controller.GerCamera());

	Swallow::Renderer2D::DrawSquare({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f }, 45.0f);
	Swallow::Renderer2D::DrawSquare({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	//Swallow::Renderer2D::DrawSquare({ 0.1f, 0.5f }, { 0.5f, 0.5f }, m_test_texture);
	Swallow::Renderer2D::DrawSquare({ 0.1f, 0.5f }, { 50.f, 50.f }, m_test_texture);

	// before Renderer2D
	//std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_shader)->Bind();
	//std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_shader)->UploadUniformFloat4("u_Color", m_square_color);
	//Swallow::Renderer::Submit(m_squareVA, m_shader, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

	Swallow::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_square_color));
	ImGui::End();
}

void Sandbox2D::OnEvent(Swallow::Event& event)
{
	m_camera_controller.OnEvent(event); 
}
