#pragma once

#include "RendererAPI.h"

#include "OrthographicCamera.h"
#include "Shader.h"

#include <memory>

namespace Swallow {

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Init();
		static void Submit(const Ref<VertexArray>& vertex_array, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_scene_data;
	};
}