#include "ParticleSystem.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#include <glm/gtx/compatibility.hpp>

std::mt19937 Random::s_random_engine;
std::uniform_int_distribution<std::mt19937::result_type> Random::s_distribution;

// attention: render part begin from 0 to 1000 find fallow particle 
//            emit part should decrease to set particle

ParticleSystem::ParticleSystem(uint32_t max_particles):
	m_pool_index(max_particles - 1u)
{
	m_particle_pool.resize(max_particles);
	
	for (auto& particle : m_particle_pool)
	{
		particle.is_active = false;
	}
}

void ParticleSystem::OnUpdate(Swallow::TimeStep time_step)
{
	for (auto& particle : m_particle_pool)
	{
		if (!particle.is_active)
			continue;

		if (particle.life_remaining <= 0.0f)
		{
			particle.is_active = false;
			//particle.position = { 0.0f, 0.0f };
			//particle.rotation = 0.0f;
			continue;
		}

		particle.life_remaining -= time_step;
		particle.position += particle.velocity * static_cast<float>(time_step);
		particle.rotation += 0.01f * time_step;
	}
}

void ParticleSystem::OnRender(Swallow::OrthographicCamera& camera)
{
	Swallow::Renderer2D::BeginScene(camera);
	for (auto& particle : m_particle_pool)
	{
		if (!particle.is_active)
			continue;

		float life = particle.life_remaining / particle.life_time;
		glm::vec4 color = glm::lerp(particle.color_end, particle.color_begin, life);

		float size = glm::lerp(particle.size_end, particle.size_begin, life);
		glm::vec3 position = { particle.position.x, particle.position.y, 0.5f};
		Swallow::Renderer2D::DrawRotatedRectangle(particle.position, { size, size }, particle.rotation, color);
	}
	Swallow::Renderer2D::EndScene();
}

void ParticleSystem::Emit(const ParticleProps& particle_props)
{
	Particle& particle = m_particle_pool[m_pool_index];
	particle.is_active = true;
	particle.position = particle_props.position;
	particle.rotation = Random::Float() * 2.0f * glm::pi<float>();

	// Velocity
	particle.velocity = particle_props.velocity;
	particle.velocity.x += particle_props.velocity_variation.x * (Random::Float() - 0.5f);
	particle.velocity.y += particle_props.velocity_variation.y * (Random::Float() - 0.5f);

	// Color
	particle.color_begin = particle_props.color_begin;
	particle.color_end = particle_props.color_end;

	// Time
	particle.life_time = particle_props.life_time;
	particle.life_remaining = particle_props.life_time;

	// Size
	particle.size_begin = particle_props.size_begin + particle_props.size_variation;
	particle.size_end = particle_props.size_end;

	m_pool_index = --m_pool_index % m_particle_pool.size();
}
