#include "swpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "Swallow/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Swallow {

	// must coordinate to layout
	// eg. 
	// layout:      QuadVertex:
	// position     position
	// tex_index    tex_index
	//
	// sequence cannot change!
	struct QuadVertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texture_coordinate;
		float texture_index;
		float tiling_factor;
	};

	struct Renderer2DData
	{
		static const uint32_t max_quads = 6913;
		//static const uint32_t max_quads = 2;
		static const uint32_t max_vertices = max_quads * 4;
		static const uint32_t max_indices = max_quads * 6;
		static const uint32_t max_texture_slots = 32;

		Ref<VertexArray> quad_vertex_array;
		Ref<VertexBuffer> quad_vertex_buffer;
		Ref<Shader> texture_shader;
		Ref<Texture2D> white_texture;

		uint32_t quad_idx_cnt = 0;
		QuadVertex* quadVB_base = nullptr;
		QuadVertex* quadVB_cur = nullptr;

		std::array<Ref<Texture2D>, max_texture_slots> texture_slots;
		uint32_t texture_slot_idx = 1; // 0 is default white texture

		glm::vec4 quad_vertex_positions[4];

		Renderer2D::Statistics statistics;
	};

	static Renderer2DData s_data;

	void Swallow::Renderer2D::Init()
	{
		SW_PROFILE_FUNCTION();

		s_data.quad_vertex_array = VertexArray::CreateIns();
		// before batch draw
		//float sqaure_vertices[5 * 4] = {
		//   -0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
		//	0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
		//	0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
		//   -0.75f,  0.75f, 0.0f, 0.0f, 1.0f
		//};
		//Ref<VertexBuffer> squareVB;
		//squareVB = VertexBuffer::CreateIns(sqaure_vertices, sizeof(sqaure_vertices));

		s_data.quad_vertex_buffer = VertexBuffer::CreateIns(s_data.max_vertices * sizeof(QuadVertex));

		// layout
		s_data.quad_vertex_buffer->SetLayout({
			{ShaderDataType::Float3, "a_Position" },
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TexCoord" },
			{ShaderDataType::Float,  "a_TexIndex" },
			{ShaderDataType::Float,  "a_TilingFactor"}
			});
		s_data.quad_vertex_array->AddVertexBuffer(s_data.quad_vertex_buffer);

		s_data.quadVB_base = new QuadVertex[s_data.max_vertices];

		uint32_t* quad_indices = new uint32_t[s_data.max_indices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_data.max_indices; i += 6)
		{
			quad_indices[i + 0] = offset + 0;
			quad_indices[i + 1] = offset + 1;
			quad_indices[i + 2] = offset + 2;

			quad_indices[i + 3] = offset + 2;
			quad_indices[i + 4] = offset + 3;
			quad_indices[i + 5] = offset + 0;

			offset += 4;
		}
		Ref<IndexBuffer> squareIB = IndexBuffer::CreateIns(quad_indices, s_data.max_indices);
		s_data.quad_vertex_array->SetIndexBuffer(squareIB);
		delete[] quad_indices;

		// default white texture
		s_data.white_texture = Texture2D::CreateIns(1, 1);
		uint32_t white_texture_data = 0xffffffff;
		s_data.white_texture->SetData(&white_texture_data, sizeof(uint32_t));

		int32_t samplers[s_data.max_texture_slots];
		for (uint32_t i = 0; i < s_data.max_texture_slots; ++i)
			samplers[i] = i;

		s_data.texture_shader = Shader::CreateIns("assets/shaders/Texture.glsl");
		s_data.texture_shader->Bind();
		s_data.texture_shader->SetIntArray("u_Textures", samplers, s_data.max_texture_slots);

		s_data.texture_slots[0] = s_data.white_texture;

		s_data.quad_vertex_positions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_data.quad_vertex_positions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_data.quad_vertex_positions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_data.quad_vertex_positions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

	}

	void Renderer2D::Shutdown()
	{
		SW_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		SW_PROFILE_FUNCTION();

		//RenderCommand::SetDepthTest(false);

		s_data.texture_shader->Bind();
		s_data.texture_shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_data.quad_idx_cnt = 0;
		s_data.quadVB_cur = s_data.quadVB_base;
		s_data.texture_slot_idx = 1;
	}

	void Renderer2D::EndScene()
	{
		SW_PROFILE_FUNCTION();

		//RenderCommand::SetDepthTest(true);

		uint32_t data_size = reinterpret_cast<uint8_t*>(s_data.quadVB_cur) - reinterpret_cast<uint8_t*>(s_data.quadVB_base);

		// upload data(layout in glsl) from QuadVertex to OpenGL
		s_data.quad_vertex_buffer->SetData(s_data.quadVB_base, data_size);

		Flush();
	}

	void Renderer2D::Flush()
	{
		SW_PROFILE_FUNCTION();

		for (uint32_t i = 0; i < s_data.texture_slot_idx; ++i)
			s_data.texture_slots[i]->Bind(i);

		RenderCommand::DrawIndexd(s_data.quad_vertex_array, s_data.quad_idx_cnt);

		++s_data.statistics.DrawCalls;
	}

	void Renderer2D::EndAndReset()
	{
		EndScene();

		//RenderCommand::SetDepthTest(false);

		s_data.quad_idx_cnt = 0;
		s_data.quadVB_cur = s_data.quadVB_base;
		s_data.texture_slot_idx = 1;
	}

	void Renderer2D::DrawRectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawRectangle({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawRectangle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		SW_PROFILE_FUNCTION();

		if (s_data.quad_idx_cnt >= Renderer2DData::max_indices)
			EndAndReset();

		constexpr float texture_idx = 0.0f;
		constexpr float tiling_factor = 1.0f;

		constexpr size_t quad_vertex_cnt = 4;
		static const glm::vec2 texture_coords[4] = 
			{ {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < quad_vertex_cnt; ++i)
		{
			s_data.quadVB_cur->position = transform * s_data.quad_vertex_positions[i];
			s_data.quadVB_cur->color = color;
			s_data.quadVB_cur->texture_coordinate = texture_coords[i];
			s_data.quadVB_cur->texture_index = texture_idx;
			s_data.quadVB_cur->tiling_factor = tiling_factor;
			++s_data.quadVB_cur;
		}

		//s_data.quadVB_cur->position = position;
		//s_data.quadVB_cur->color = color;
		//s_data.quadVB_cur->texture_coordinate = { 0.0f, 0.0f };
		//s_data.quadVB_cur->texture_index = white_texture_idx;
		//s_data.quadVB_cur->tiling_factor = default_tiling_factor;
		//++s_data.quadVB_cur;
		//
		//s_data.quadVB_cur->position = { position.x + size.x, position.y, 0.0f };
		//s_data.quadVB_cur->color = color;
		//s_data.quadVB_cur->texture_coordinate = { 1.0f, 0.0f };		
		//s_data.quadVB_cur->texture_index = white_texture_idx;
		//s_data.quadVB_cur->tiling_factor = default_tiling_factor;
		//++s_data.quadVB_cur;
		//
		//s_data.quadVB_cur->position = { position.x + size.x, position.y + size.y, 0.0f };
		//s_data.quadVB_cur->color = color;
		//s_data.quadVB_cur->texture_coordinate = { 1.0f, 1.0f };
		//s_data.quadVB_cur->texture_index = white_texture_idx;
		//s_data.quadVB_cur->tiling_factor = default_tiling_factor;
		//++s_data.quadVB_cur;
		//
		//s_data.quadVB_cur->position = { position.x, position.y + size.y, 0.0f };
		//s_data.quadVB_cur->color = color;
		//s_data.quadVB_cur->texture_coordinate = { 0.0f, 1.0f };
		//s_data.quadVB_cur->texture_index = white_texture_idx;
		//s_data.quadVB_cur->tiling_factor = default_tiling_factor;
		//++s_data.quadVB_cur;

		s_data.quad_idx_cnt += 6;

		++s_data.statistics.QuadCount;
		//s_data.white_texture->Bind(); // bind the default white texture
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
		//	* glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		//s_data.texture_shader->SetMat4("u_Transform", transform);
		//s_data.quad_vertex_array->Bind();
		//RenderCommand::DrawIndexd(s_data.quad_vertex_array);
	}

	void Renderer2D::DrawRectangle(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4 tint_color)
	{
		DrawRectangle({ position.x, position.y, 0.0f }, size, texture, tiling_factor, tint_color);

	}

	void Renderer2D::DrawRectangle(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4 tint_color)
	{
		SW_PROFILE_FUNCTION();

		if (s_data.quad_idx_cnt >= Renderer2DData::max_indices)
			EndAndReset();

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		constexpr size_t quad_vertex_cnt = 4;
		static const glm::vec2 texture_coords[4] =
			{ {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };

		float texture_idx = 0.0f;

		for (uint32_t i = 1; i < s_data.texture_slot_idx; ++i)
		{
			if (*s_data.texture_slots[i].get() == *texture.get())
			{
				texture_idx = static_cast<float>(i);
				break;
			}
		}
		 
		// if didn't find, then added it
		if (texture_idx == 0.0f)
		{
			texture_idx = static_cast<float>(s_data.texture_slot_idx);
			s_data.texture_slots[s_data.texture_slot_idx] = texture;
			++s_data.texture_slot_idx;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < quad_vertex_cnt; ++i)
		{
			s_data.quadVB_cur->position = transform * s_data.quad_vertex_positions[i];
			s_data.quadVB_cur->color = color;
			s_data.quadVB_cur->texture_coordinate = texture_coords[i];
			s_data.quadVB_cur->texture_index = texture_idx;
			s_data.quadVB_cur->tiling_factor = tiling_factor;
			++s_data.quadVB_cur;
		}

		// old 
		//s_data.quadVB_cur->position = position;
		//s_data.quadVB_cur->color = color;
		//s_data.quadVB_cur->texture_coordinate = { 0.0f, 0.0f };
		//s_data.quadVB_cur->texture_index = texture_idx;
		//s_data.quadVB_cur->tiling_factor = tiling_factor;
		//++s_data.quadVB_cur;
		//
		//s_data.quadVB_cur->position = { position.x + size.x, position.y, 0.0f };
		//s_data.quadVB_cur->color = color;
		//s_data.quadVB_cur->texture_coordinate = { 1.0f, 0.0f };
		//s_data.quadVB_cur->texture_index = texture_idx;
		//s_data.quadVB_cur->tiling_factor = tiling_factor;
		//++s_data.quadVB_cur;
		//
		//s_data.quadVB_cur->position = { position.x + size.x, position.y + size.y, 0.0f };
		//s_data.quadVB_cur->color = color;
		//s_data.quadVB_cur->texture_coordinate = { 1.0f, 1.0f };
		//s_data.quadVB_cur->texture_index = texture_idx;
		//s_data.quadVB_cur->tiling_factor = tiling_factor;
		//++s_data.quadVB_cur;
		// 
		//s_data.quadVB_cur->position = { position.x, position.y + size.y, 0.0f };
		//s_data.quadVB_cur->color = color;
		//s_data.quadVB_cur->texture_coordinate = { 0.0f, 1.0f };
		//s_data.quadVB_cur->texture_index = texture_idx;
		//s_data.quadVB_cur->tiling_factor = tiling_factor;
		//++s_data.quadVB_cur;

		s_data.quad_idx_cnt += 6;

		++s_data.statistics.QuadCount;

		//s_data.texture_shader->SetFloat4("u_Color", tint_color);
		//texture->Bind();
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		//	* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		//s_data.texture_shader->SetMat4("u_Transform", transform);
		//s_data.quad_vertex_array->Bind();
		//RenderCommand::DrawIndexd(s_data.quad_vertex_array);
	}

	void Renderer2D::DrawRectangle(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, float tiling_factor, const glm::vec4 tint_color)
	{
		DrawRectangle({ position.x, position.y, 0.0f }, size, subtexture, tiling_factor, tint_color);
	}

	void Renderer2D::DrawRectangle(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, float tiling_factor, const glm::vec4 tint_color)
	{
		SW_PROFILE_FUNCTION();

		if (s_data.quad_idx_cnt >= Renderer2DData::max_indices)
			EndAndReset();

		const glm::vec2* texture_coords = subtexture->GetTexCoords();
		const Ref<Texture2D> texture = subtexture->GetTexture();

		constexpr size_t quad_vertex_cnt = 4;

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float texture_idx = 0.0f;

		for (uint32_t i = 1; i < s_data.texture_slot_idx; ++i)
		{
			if (*s_data.texture_slots[i].get() == *texture.get())
			{
				texture_idx = static_cast<float>(i);
				break;
			}
		}

		// if didn't find, then added it
		if (texture_idx == 0.0f)
		{
			texture_idx = static_cast<float>(s_data.texture_slot_idx);
			s_data.texture_slots[s_data.texture_slot_idx] = texture;
			++s_data.texture_slot_idx;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < quad_vertex_cnt; ++i)
		{
			s_data.quadVB_cur->position = transform * s_data.quad_vertex_positions[i];
			s_data.quadVB_cur->color = color;
			s_data.quadVB_cur->texture_coordinate = texture_coords[i];
			s_data.quadVB_cur->texture_index = texture_idx;
			s_data.quadVB_cur->tiling_factor = tiling_factor;
			++s_data.quadVB_cur;
		}
		s_data.quad_idx_cnt += 6;

		++s_data.statistics.QuadCount;
	}

	void Renderer2D::DrawRotatedRectangle(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedRectangle({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedRectangle(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		SW_PROFILE_FUNCTION();

		if (s_data.quad_idx_cnt >= Renderer2DData::max_indices)
			EndAndReset();

		constexpr size_t quad_vertex_cnt = 4;
		constexpr float white_texture_idx = 0.0f;
		constexpr float default_tiling_factor = 1.0f;

		static const glm::vec2 texture_coords[4] =
		{ {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < quad_vertex_cnt; ++i)
		{
			s_data.quadVB_cur->position = transform * s_data.quad_vertex_positions[i];
			s_data.quadVB_cur->color = color;
			s_data.quadVB_cur->texture_coordinate = texture_coords[i];
			s_data.quadVB_cur->texture_index = white_texture_idx;
			s_data.quadVB_cur->tiling_factor = default_tiling_factor;
			++s_data.quadVB_cur;
		}

		s_data.quad_idx_cnt += 6;

		++s_data.statistics.QuadCount;
	}

	void Renderer2D::DrawRotatedRectangle(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4 tint_color)
	{
		DrawRotatedRectangle({ position.x, position.y, 0.0f }, size, rotation, texture, tiling_factor, tint_color);
	}

	void Renderer2D::DrawRotatedRectangle(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4 tint_color)
	{
		SW_PROFILE_FUNCTION();

		if (s_data.quad_idx_cnt >= Renderer2DData::max_indices)
			EndAndReset();

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		static const glm::vec2 texture_coords[4] =
			{ {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };

		float texture_idx = 0.0f;

		for (uint32_t i = 1; i < s_data.texture_slot_idx; ++i)
		{
			if (*s_data.texture_slots[i].get() == *texture.get())
			{
				texture_idx = static_cast<float>(i);
				break;
			}
		}

		// if didn't find, then added it
		if (texture_idx == 0.0f)
		{
			texture_idx = static_cast<float>(s_data.texture_slot_idx);
			s_data.texture_slots[s_data.texture_slot_idx] = texture;
			++s_data.texture_slot_idx;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < 4; ++i)
		{
			s_data.quadVB_cur->position = transform * s_data.quad_vertex_positions[i];
			s_data.quadVB_cur->color = color;
			s_data.quadVB_cur->texture_coordinate = texture_coords[i];
			s_data.quadVB_cur->texture_index = texture_idx;
			s_data.quadVB_cur->tiling_factor = tiling_factor;
			++s_data.quadVB_cur;
		}

		s_data.quad_idx_cnt += 6;

		++s_data.statistics.QuadCount;
	}

	void Renderer2D::DrawRotatedRectangle(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, float tiling_factor, const glm::vec4 tint_color)
	{
		DrawRotatedRectangle({ position.x, position.y, 0.0f }, size, rotation, subtexture, tiling_factor, tint_color);
	}

	void Renderer2D::DrawRotatedRectangle(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, float tiling_factor, const glm::vec4 tint_color)
	{
		SW_PROFILE_FUNCTION();

		if (s_data.quad_idx_cnt >= Renderer2DData::max_indices)
			EndAndReset();

		const glm::vec2* texture_coords = subtexture->GetTexCoords();
		const Ref<Texture2D> texture = subtexture->GetTexture();

		constexpr size_t quad_vertex_cnt = 4;
		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float texture_idx = 0.0f;

		for (uint32_t i = 1; i < s_data.texture_slot_idx; ++i)
		{
			if (*s_data.texture_slots[i].get() == *texture.get())
			{
				texture_idx = static_cast<float>(i);
				break;
			}
		}

		// if didn't find, then added it
		if (texture_idx == 0.0f)
		{
			texture_idx = static_cast<float>(s_data.texture_slot_idx);
			s_data.texture_slots[s_data.texture_slot_idx] = texture;
			++s_data.texture_slot_idx;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < quad_vertex_cnt; ++i)
		{
			s_data.quadVB_cur->position = transform * s_data.quad_vertex_positions[i];
			s_data.quadVB_cur->color = color;
			s_data.quadVB_cur->texture_coordinate = texture_coords[i];
			s_data.quadVB_cur->texture_index = texture_idx;
			s_data.quadVB_cur->tiling_factor = tiling_factor;
			++s_data.quadVB_cur;
		}

		s_data.quad_idx_cnt += 6;

		++s_data.statistics.QuadCount;
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_data.statistics;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_data.statistics, 0, sizeof(Statistics));
	}
}