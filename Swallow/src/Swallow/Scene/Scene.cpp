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
			auto view = m_registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto& [transform_cp, camera_cp] = view.get<TransformComponent, CameraComponent>(entity);

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

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_viewport_width = width;
		m_viewport_height = height;

		auto view = m_registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& camera_component = view.get<CameraComponent>(entity);
			if (!camera_component.is_aspect_ratio_fixed)
				camera_component.camera.SetViewportSize(width, height);
		}
	}
}