#include "swpch.h"
#include "Scene.h"

#include "Components.h"
#include "Swallow/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

namespace Swallow {

	Scene::Scene()
	{
		entt::entity entity = m_registry.create();
	}
	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_registry.create(), this };

		// default have transform and tag component
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>(name);
		tag.tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(TimeStep time_step)
	{
		auto group = m_registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawRectangle(transform, sprite.color);
		}

	}
}