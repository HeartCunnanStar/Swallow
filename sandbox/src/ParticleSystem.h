#pragma once

#include <Swallow.h>

#include <random>

class Random
{
public:
	static void Init()
	{
		s_random_engine.seed(std::random_device()());
	}
	static float Float()
	{
		return static_cast<float>(s_distribution(s_random_engine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
	}

private:
	static std::mt19937 s_random_engine;
	static std::uniform_int_distribution<std::mt19937::result_type> s_distribution;
};


struct ParticleProps
{
	glm::vec2 position;
	glm::vec2 velocity, velocity_variation;
	glm::vec4 color_begin, color_end;
	float size_begin, size_end, size_variation;
	float life_time = 1.0f;
};

class ParticleSystem
{
public:
	ParticleSystem(uint32_t max_particles = 2006u);

	void OnUpdate(Swallow::TimeStep ts);
	void OnRender(Swallow::OrthographicCamera& camera);

	void Emit(const ParticleProps& particle_props);

private:
	struct Particle
	{
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec4 color_begin, color_end;
		float rotation = 0.0f;
		float size_begin, size_end;

		float life_time = 1.0f;
		float life_remaining = 0.0f;

		bool is_active = false;
	};

	std::vector<Particle> m_particle_pool;
	uint32_t m_pool_index;
};