#include "swpch.h"
#include "Scene.h"

#include "Components.h"

#include <glm/glm.hpp>

namespace Swallow {

	Scene::Scene()
	{
		entt::entity entity = m_registry.create();
	}
	Scene::~Scene()
	{
	}

	entt::entity Scene::CreateEntity()
	{
		return entt::entity();
	}

	void Scene::OnUpdate(TimeStep time_step)
	{
		auto group = m_registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
		}

	}
}