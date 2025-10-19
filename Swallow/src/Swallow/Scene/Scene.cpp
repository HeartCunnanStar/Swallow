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
		Camera* primary_camera = nullptr;
		glm::mat4* camera_tranform = nullptr;

		{
			auto group = m_registry.view<TransformComponent, CameraComponent>();
			for (auto entity : group)
			{
				auto& [transform_cp, camera_cp] = group.get<TransformComponent, CameraComponent>(entity);

				// find the primary camera;
				if (camera_cp.is_primary)
				{
					primary_camera = &camera_cp.camera;
					camera_tranform = &transform_cp.transform;
					break;
				}
			}
		}

		if (primary_camera)
		{
			Renderer2D::BeginScene(primary_camera->GetProjetionMatrix(), *camera_tranform);

			auto group = m_registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawRectangle(transform, sprite.color);
			}

			Renderer2D::EndScene();
		}
	}
}