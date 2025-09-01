#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Swallow {

	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();
		
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawSquare(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation = 0.0f);
		static void DrawSquare(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation = 0.0f);
		static void DrawSquare(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture, float rotation = 0.0f);
		static void DrawSquare(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, float rotation = 0.0f);
	};
}