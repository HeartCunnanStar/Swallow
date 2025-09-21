#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"
#include "SubTexture2D.h"

namespace Swallow {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Flush();

		static void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawRectangle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));
		static void DrawRectangle(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));
		static void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));
		static void DrawRectangle(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));

		// Impl
		static void DrawRectangle(const glm::mat4& transform, const glm::vec4& color);
		static void DrawRectangle(const glm::mat4& transform, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));
		static void DrawRectangle(const glm::mat4& transform, const Ref<SubTexture2D>& subtexture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));
	
		static void DrawRotatedRectangle(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedRectangle(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedRectangle(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));
		static void DrawRotatedRectangle(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));
		static void DrawRotatedRectangle(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));
		static void DrawRotatedRectangle(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));

		// Impl
		static void DrawRotatedRectangle(const glm::mat4& transform, const glm::vec4& color);
		static void DrawRotatedRectangle(const glm::mat4& transform, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));
		static void DrawRotatedRectangle(const glm::mat4& transform, const Ref<SubTexture2D>& subtexture, float tiling_factor = 1.0f, const glm::vec4 tint_color = glm::vec4(1.0f));

		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		static Statistics GetStats();
		static void ResetStats();

	private:
		static void EndAndReset();
	};
};