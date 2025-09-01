#include "swpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "Swallow/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Swallow {

	struct Renderer2DStorage
	{
		Ref<VertexArray> square_vertex_array;
		Ref<Shader> flat_color_shader;
	};

	static Renderer2DStorage* s_data;

	void Swallow::Renderer2D::Init()
	{
		s_data = new Renderer2DStorage();

		s_data->square_vertex_array = VertexArray::CreateIns();
		float sqaure_vertices[5 * 4] = {
		   -0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f,  0.75f, 0.0f,
		   -0.75f,  0.75f, 0.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::CreateIns(sqaure_vertices, sizeof(sqaure_vertices)));

		// layout
		BufferLayout square_layout = {
			{ShaderDataType::Float3, "a_Position" }
		};

		squareVB->SetLayout(square_layout);
		s_data->square_vertex_array->AddVertexBuffer(squareVB);

		unsigned int square_indicies[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::CreateIns(square_indicies, sizeof(square_indicies) / sizeof(uint32_t)));
		s_data->square_vertex_array->SetIndexBuffer(squareIB);

		s_data->flat_color_shader = Shader::CreateIns("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::ShutDown()
	{
		delete s_data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_data->flat_color_shader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_data->flat_color_shader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(s_data->flat_color_shader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawSquare(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawSquare({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawSquare(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<Swallow::OpenGLShader>(s_data->flat_color_shader)->Bind();
		std::dynamic_pointer_cast<Swallow::OpenGLShader>(s_data->flat_color_shader)->UploadUniformFloat4("u_Color", color);

		s_data->square_vertex_array->Bind();
		RenderCommand::DrawIndexed(s_data->square_vertex_array);
	}
}