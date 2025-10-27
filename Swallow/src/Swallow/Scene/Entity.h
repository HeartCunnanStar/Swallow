#pragma once

#include "Scene.h"

#include <entt.hpp>

namespace Swallow{

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity m_entity_handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args... args)
		{
			SW_CORE_ASSERT(!HasComponent<T>(), "Entity already had one component!");

			return m_scene->m_registry.emplace<T>(m_entity_handle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			SW_CORE_ASSERT(HasComponent<T>(), "Entity has no component!");

			return m_scene->m_registry.get<T>(m_entity_handle);
		}

		template<typename T>
		void RemoveComponent()
		{
			SW_CORE_ASSERT(HasComponent<T>(), "Entity has no component!");

			m_scene->m_registry.remove<T>.has(m_entity_handle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_scene->m_registry.all_of<T>(m_entity_handle);
		}

		operator bool() const { return static_cast<int>(m_entity_handle) != 0; }

	private:
		entt::entity m_entity_handle{ entt::null };
		Scene* m_scene = nullptr;
	};
}