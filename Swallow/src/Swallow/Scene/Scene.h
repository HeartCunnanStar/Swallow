#pragma once

#include "entt.hpp"

#include "Swallow/Core/TimeStep.h"

namespace Swallow {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		// Temp
		entt::registry& Reg() { return m_registry; }

		void OnUpdate(TimeStep time_step);
		void OnViewportResize(uint32_t width, uint32_t height);

	private:
		entt::registry m_registry;
		uint32_t m_viewport_width = 0;
		uint32_t m_viewport_height = 0;

		friend class Entity;
	};
}