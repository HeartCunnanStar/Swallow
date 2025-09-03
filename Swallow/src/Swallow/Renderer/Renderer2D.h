#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Swallow {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();
		
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawSquare(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawSquare(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawSquare(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));
		static void DrawSquare(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));

		static void DrawRotatedSquare(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedSquare(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedSquare(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));
		static void DrawRotatedSquare(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));


	};
}