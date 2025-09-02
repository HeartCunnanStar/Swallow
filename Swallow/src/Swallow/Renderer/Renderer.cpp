#include "swpch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer2D.h"

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

	void Renderer::Init()
	{
		SW_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWinodwResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::Submit(const Ref<VertexArray>& vertex_array, const Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_scene_data->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertex_array->Bind();
		RenderCommand::DrawIndexed(vertex_array);
	}
}