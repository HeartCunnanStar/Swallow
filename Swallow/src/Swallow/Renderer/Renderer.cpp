#include "swpch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Swallow
{
	Renderer::SceneData* Renderer::m_scene_data = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_scene_data->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertex_array, const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_scene_data->ViewProjectionMatrix);
		vertex_array->Bind();
		RenderCommand::DrawIndexed(vertex_array);
	}
}