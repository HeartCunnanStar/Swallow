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
		static void Submit(const std::shared_ptr<VertexArray>& vertex_array, const std::shared_ptr<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_scene_data;
	};
}