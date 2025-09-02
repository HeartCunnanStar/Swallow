#pragma once

#include "RendererAPI.h"

#include "OrthographicCamera.h"
#include "Shader.h"

#include <memory>

namespace Swallow {

	class Renderer
	{
	public:
		static void Init();
		static void OnWinodwResize(uint32_t width, uint32_t height);
		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);
		static void Submit(const Ref<VertexArray>& vertex_array, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void EndScene();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_scene_data;
	};
}