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
		Ref<Shader> texture_shader;
		Ref<Texture2D> white_texture;
	};

	static Renderer2DStorage* s_data;

	void Swallow::Renderer2D::Init()
	{
		SW_PROFILE_FUNCTION();

		s_data = new Renderer2DStorage();

		s_data->square_vertex_array = VertexArray::CreateIns();
		float sqaure_vertices[5 * 4] = {
		   -0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
		   -0.75f,  0.75f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB = VertexBuffer::CreateIns(sqaure_vertices, sizeof(sqaure_vertices));

		// layout
		BufferLayout square_layout = {
			{ShaderDataType::Float3, "a_Position" },
			{ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(square_layout);
		s_data->square_vertex_array->AddVertexBuffer(squareVB);

		unsigned int square_indicies[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB = IndexBuffer::CreateIns(square_indicies, sizeof(square_indicies) / sizeof(uint32_t));
		s_data->square_vertex_array->SetIndexBuffer(squareIB);

		s_data->white_texture = Texture2D::CreateIns(1, 1);
		uint32_t white_texture_data = 0xffffffff;
		s_data->white_texture->SetData(&white_texture_data, sizeof(uint32_t));

		s_data->texture_shader = Shader::CreateIns("assets/shaders/Texture.glsl");
		s_data->texture_shader->Bind();
		s_data->texture_shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		SW_PROFILE_FUNCTION();

		delete s_data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		SW_PROFILE_FUNCTION();

		s_data->texture_shader->Bind();
		s_data->texture_shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		SW_PROFILE_FUNCTION();

	}

	void Renderer2D::DrawSquare(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawSquare({ position.x, position.y, 0.0f }, size, color);
	}

	// 
	void Renderer2D::DrawSquare(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		SW_PROFILE_FUNCTION();

		s_data->texture_shader->SetFloat4("u_Color", color);
		s_data->texture_shader->SetFloat("u_TilingFactor", 1.0f);
		s_data->white_texture->Bind(); // bind the default white texture

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
			* glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

		s_data->texture_shader->SetMat4("u_Transform", transform);

		s_data->square_vertex_array->Bind();
		RenderCommand::DrawIndexed(s_data->square_vertex_array);
	}

	void Renderer2D::DrawSquare(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture, float tiling_factor, const glm::vec4 tint_color)
	{
		DrawSquare({ position.x, position.y, 0.0f }, size, texture, tiling_factor, tint_color);

	}

	void Renderer2D::DrawSquare(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, float tiling_factor, const glm::vec4 tint_color)
	{
		SW_PROFILE_FUNCTION();

		s_data->texture_shader->SetFloat4("u_Color", tint_color);
		s_data->texture_shader->SetFloat("u_TilingFactor", tiling_factor);

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_data->texture_shader->SetMat4("u_Transform", transform);

		s_data->square_vertex_array->Bind();
		RenderCommand::DrawIndexed(s_data->square_vertex_array);
	}

	void Renderer2D::DrawRotatedSquare(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedSquare({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedSquare(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		SW_PROFILE_FUNCTION();

		s_data->texture_shader->SetFloat4("u_Color", color);
		s_data->texture_shader->SetFloat("u_TilingFactor", 1.0f);
		s_data->white_texture->Bind(); // bind the default white texture

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_data->texture_shader->SetMat4("u_Transform", transform);

		s_data->square_vertex_array->Bind();
		RenderCommand::DrawIndexed(s_data->square_vertex_array);
	}

	void Renderer2D::DrawRotatedSquare(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tiling_factor, const glm::vec4 tint_color)
	{
		DrawRotatedSquare({ position.x, position.y, 0.0f }, size, rotation, texture, tiling_factor, tint_color);
	}

	void Renderer2D::DrawRotatedSquare(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tiling_factor, const glm::vec4 tint_color)
	{
		SW_PROFILE_FUNCTION();

		s_data->texture_shader->SetFloat4("u_Color", tint_color);
		s_data->texture_shader->SetFloat("u_TilingFactor", tiling_factor);

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_data->texture_shader->SetMat4("u_Transform", transform);

		s_data->square_vertex_array->Bind();
		RenderCommand::DrawIndexed(s_data->square_vertex_array);
	}
}