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

	private:
		entt::registry m_registry;

		friend class Entity;
	};
}