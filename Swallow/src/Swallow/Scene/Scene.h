#pragma once

#include "entt.hpp"

#include "Swallow/Core/TimeStep.h"

namespace Swallow {

	class Scene
	{
	public:
		Scene();
		~Scene();

		// Temp
		entt::entity CreateEntity();

		// Temp
		entt::registry& Reg() { return m_registry; }

		void OnUpdate(TimeStep time_step);

	private:
		entt::registry m_registry;
	};
}