#pragma once

#include <Swallow.h>

#include "ParticleSystem.h"

class Sandbox2D : public Swallow::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Swallow::TimeStep time_step) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Swallow::Event& event) override;

private:
	Swallow::OrthographicCameraController m_camera_controller;

	// FOR DEBUG : will remove soon
	Swallow::Ref<Swallow::VertexArray> m_squareVA;
	Swallow::Ref<Swallow::Shader> m_shader;

	Swallow::Ref<Swallow::Texture2D> m_test_texture;
	Swallow::Ref<Swallow::Texture2D> m_bg_texture;

	Swallow::Ref<Swallow::Texture2D> m_sprite_sheet;

	glm::vec4 m_square_color = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_particle_system;
	ParticleProps m_particle;
	//struct PerformanceData
	//{
	//	const char* name;
	//	float time;
	//};
	//std::vector<PerformanceData> m_performance_result;
};