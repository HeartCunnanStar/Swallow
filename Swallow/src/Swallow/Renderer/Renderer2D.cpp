#include "swpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "Swallow/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Swallow {

	struct Renderer2DStorage
	{
		Ref<VertexArray> square_vertex_array;
		Ref<Shader> flat_color_shader;
		Ref<Shader> texture_shader;
	};

	static Renderer2DStorage* s_data;

	void Swallow::Renderer2D::Init()
	{
		s_data = new Renderer2DStorage();

		s_data->square_vertex_array = VertexArray::CreateIns();
		float sqaure_vertices[5 * 4] = {
		   -0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
		   -0.75f,  0.75f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::CreateIns(sqaure_vertices, sizeof(sqaure_vertices)));

		// layout
		BufferLayout square_layout = {
			{ShaderDataType::Float3, "a_Position" },
			{ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(square_layout);
		s_data->square_vertex_array->AddVertexBuffer(squareVB);

		unsigned int square_indicies[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::CreateIns(square_indicies, sizeof(square_indicies) / sizeof(uint32_t)));
		s_data->square_vertex_array->SetIndexBuffer(squareIB);

		s_data->flat_color_shader = Shader::CreateIns("assets/shaders/FlatColor.glsl");
		s_data->texture_shader = Shader::CreateIns("assets/shaders/Texture.glsl");

		s_data->texture_shader->Bind();
		s_data->texture_shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::ShutDown()
	{
		delete s_data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_data->flat_color_shader->Bind();
		s_data->flat_color_shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_data->texture_shader->Bind();
		s_data->texture_shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawSquare(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		DrawSquare({ position.x, position.y, 0.0f }, size, color, rotation);
	}

	// 
	void Renderer2D::DrawSquare(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		s_data->flat_color_shader->Bind();
		s_data->flat_color_shader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		s_data->flat_color_shader->SetMat4("u_Transform", transform);

		s_data->square_vertex_array->Bind();
		RenderCommand::DrawIndexed(s_data->square_vertex_array);
	}

	void Renderer2D::DrawSquare(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture, float rotation)
	{
		DrawSquare({ position.x, position.y, 0.0f }, size, texture, rotation);

	}

	void Renderer2D::DrawSquare(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, float rotation)
	{
		s_data->texture_shader->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_data->texture_shader->SetMat4("u_Transform", transform);

		texture->Bind();

		s_data->square_vertex_array->Bind();
		RenderCommand::DrawIndexed(s_data->square_vertex_array);
	}
}