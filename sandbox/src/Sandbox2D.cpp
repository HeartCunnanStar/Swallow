#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include <chrono>
//template<class Fn>
//class Timer
//{
//public:
//	Timer(const char* name, Fn&& func)
//		: m_name(name), m_func(func), m_is_stopped(false)
//	{
//		m_start_timepoint = std::chrono::high_resolution_clock::now();
//	}
//
//	~Timer()
//	{
//		if (!m_is_stopped)
//			Stop();
//	}
//	void Stop()
//	{
//		auto end_timepoint = std::chrono::high_resolution_clock::now();
//
//		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_timepoint).time_since_epoch().count();
//		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();
//
//		m_is_stopped = true;
//
//		m_func({ m_name, (end - start) * 0.001f });
//	}
//
//private:
//	Fn m_func;
//	const char* m_name;
//	std::chrono::time_point<std::chrono::steady_clock> m_start_timepoint;
//	bool m_is_stopped;
//};
//
//#define SW_PERFORMANCE_SCOPE(name) Timer timer##__LINE__(name, [&](PerformanceData performance_data) { m_performance_result.push_back(performance_data); })

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_camera_controller(1280.f / 720.f)
{

}

void Sandbox2D::OnAttach()
{
	SW_PROFILE_FUNCTION();

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
	SW_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Swallow::TimeStep time_step)
{
	SW_PROFILE_FUNCTION();

	//--------------Updata-------------------
	//Timer timer("Sandbox2D::Onupdate", [&](auto performance_data) {m_porformance_result.push_back(performance_data)});
	m_camera_controller.OnUpdata(time_step);

	//--------------Render-------------------
	{
		SW_PROFILE_SCOPE("Render-pre -// void Sandbox2D::OnUpdate(Swallow::TimeStep)");
		Swallow::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Swallow::RenderCommand::Clear();
	}

	{
		SW_PROFILE_SCOPE("Render-draw -// void Sandbox2D::OnUpdate(Swallow::TimeStep");
		Swallow::Renderer2D::BeginScene(m_camera_controller.GerCamera());

		Swallow::Renderer2D::DrawSquare({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f }, 45.0f);
		Swallow::Renderer2D::DrawSquare({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		//Swallow::Renderer2D::DrawSquare({ 0.1f, 0.5f }, { 0.5f, 0.5f }, m_test_texture);
		Swallow::Renderer2D::DrawSquare({ 0.1f, 0.5f }, { 50.f, 50.f }, m_test_texture);

		Swallow::Renderer2D::EndScene();
	}
	// before Renderer2D
	//std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_shader)->Bind();
	//std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_shader)->UploadUniformFloat4("u_Color", m_square_color);
	//Swallow::Renderer::Submit(m_squareVA, m_shader, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

}

void Sandbox2D::OnImGuiRender()
{
	SW_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_square_color));

	//for (auto& result : m_performance_result)
	//{
	//	char label_buffer[64];
	//	strcpy(label_buffer, result.name);
	//	strcat(label_buffer, " %.3fms");
	//	ImGui::Text(label_buffer, result.time);
	//}
	//m_performance_result.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(Swallow::Event& event)
{
	m_camera_controller.OnEvent(event); 
}
