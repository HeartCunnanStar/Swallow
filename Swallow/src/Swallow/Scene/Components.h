#pragma once

#include <glm/glm.hpp>

#include "Swallow/Renderer/Camera.h"

namespace Swallow{

	struct TagComponent 
	{
		std::string tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: tag(tag) { }
	};

	struct TransformComponent
	{
		glm::mat4 transform = { 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: transform(transform) { }

		operator glm::mat4& () { return transform; }
		operator const glm::mat4& () const { return transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f};

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: color(color) {}

		operator glm::vec4& () { return color; }
		operator const glm::vec4& () const { return color; }
	};

	struct CameraComponent
	{
		Swallow::Camera camera;
		bool is_primary = true; // TODO: move to scene

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const glm::mat4 & projection)
			: camera(projection) { }
		
	};
}