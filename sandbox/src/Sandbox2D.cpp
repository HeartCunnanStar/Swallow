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

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_camera_controller(1280.f / 720.f, true)
{

}

void Sandbox2D::OnAttach()
{
	SW_PROFILE_FUNCTION();

	m_test_texture = Swallow::Texture2D::CreateIns("assets/textures/kita_test.png");
	m_bg_texture = Swallow::Texture2D::CreateIns("assets/textures/checkboard.png");
	//m_some_ele = Swallow::SubTexture2D::CreateFromCoords(m_sprite_sheet, {}, {});
		
	m_particle.color_begin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f },
		m_particle.color_end = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_particle.size_begin = 0.1f,
		m_particle.size_end = 0.0f;

	m_particle.size_variation = 0.3f;
	m_particle.life_time = 5.0f;
	m_particle.velocity = { 0.0f, 0.0f };
	m_particle.velocity_variation = { 3.0f, 1.0f };
	m_particle.position = { 0.0f, 0.0f };

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
	Swallow::Renderer2D::ResetStats();
	{
		SW_PROFILE_SCOPE("Render-pre -// void Sandbox2D::OnUpdate(Swallow::TimeStep)");
		Swallow::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Swallow::RenderCommand::Clear();
	}

	{
		SW_PROFILE_SCOPE("Render-draw -// void Sandbox2D::OnUpdate(Swallow::TimeStep");

		static float rotation = 0.0f;
		rotation += time_step * 30.f;
		rotation = rotation > 180.f ? -180.f : rotation;
		if (rotation >= 18000.f)
			SW_CORE_ASSERT(false, "too big");

		Swallow::Renderer2D::BeginScene(m_camera_controller.GetCamera());

		//Swallow::Renderer2D::DrawRotatedRectangle({ -1.0f, 0.0f }, { 0.8f, 0.8f }, 45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		//Swallow::Renderer2D::DrawRectangle({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		//Swallow::Renderer2D::DrawRotatedRectangle({ 0.5f, -0.5f }, { 0.5f, 0.75f }, 45.0f, m_test_texture, 10.f, { 0.8f, 0.2f, 0.3f, 1.0f });
		//Swallow::Renderer2D::DrawRectangle({ 0.0f, 0.2f }, { 0.5f, 0.5f }, { 1.0f, 1.0f, 0.8f, 1.0f });
		//Swallow::Renderer2D::DrawRotatedRectangle({ 0.0f, 0.2f }, { 0.5f, 0.5f }, rotation, { 1.0f, 1.0f, 0.8f, 1.0f });
		//Swallow::Renderer2D::DrawRectangle({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Swallow::Renderer2D::DrawRectangle({ -5.f, -5.f, -0.1f }, { 50.f, 50.f }, m_bg_texture, 100.0f, glm::vec4(0.2f, 0.9f, 0.9f, 1.0f));
		Swallow::Renderer2D::DrawRotatedRectangle({ 0.0f, 0.0f }, { 0.5f, 0.5f }, glm::radians(0.f), m_test_texture, 1.0f);
		Swallow::Renderer2D::DrawRotatedRectangle({ 0.0f, 0.0f }, { 0.5f, 0.5f }, glm::radians(rotation), m_test_texture, 1.0f);
		Swallow::Renderer2D::DrawRectangle({ 0.0f, 0.0f }, { 0.5f, 0.5f }, m_test_texture, 1.0f);

		Swallow::Renderer2D::EndScene();

		// scene2 test
		Swallow::Renderer2D::BeginScene(m_camera_controller.GetCamera());

		//for (float y = -5.0f; y < 5.0f; y += 0.5f)
		//	for (float x = -5.0f; x < 5.0f; x += 0.5f)
		//	{
		//		glm::vec4 color  = { (x + 5.f) / 10.f, 0.4f, (y + 5.f) / 10.f, 0.7f};
		//		Swallow::Renderer2D::DrawRectangle({ x, y }, { 0.45f, 0.45f }, color);
		//	}

		Swallow::Renderer2D::EndScene();

	}

	if (Swallow::Input::IsMouseButtonDown(SW_MOUSE_BUTTON_LEFT))
	{
		SW_PROFILE_SCOPE("particle render -// void Sandbox2D::OnUpdate(Swallow::TimeStep");
;
		auto [x, y] = Swallow::Input::GetMousePos();
		auto width = Swallow::Application::GetIns().GetWindow().GetWidth();
		auto height = Swallow::Application::GetIns().GetWindow().GetHeight();

		auto bounds = m_camera_controller.GetBounds();
		auto pos = m_camera_controller.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_particle.position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 1; i++)
			m_particle_system.Emit(m_particle);
	}
	m_particle_system.OnUpdate(time_step);
	m_particle_system.OnRender(m_camera_controller.GetCamera());

	// before Renderer2D
	//std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_shader)->Bind();
	//std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_shader)->UploadUniformFloat4("u_Color", m_square_color);
	//Swallow::Renderer::Submit(m_squareVA, m_shader, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
}

void Sandbox2D::OnImGuiRender()
{
	SW_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto status = Swallow::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats");
	ImGui::Text("Draw Calls: %d", status.DrawCalls);
	ImGui::Text("Quads:      %d", status.QuadCount);
	ImGui::Text("Vertices:   %d", status.GetTotalVertexCount());
	ImGui::Text("Indices:    %d", status.GetTotalIndexCount());

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
