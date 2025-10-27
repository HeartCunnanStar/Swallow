#include "swpch.h"
#include "SubTexture2D.h"

namespace Swallow {

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: m_texture(texture)
	{
		m_texture_coords[0] = { min.x, min.y };
		m_texture_coords[1] = { max.x, min.y };
		m_texture_coords[2] = { max.x, max.y };
		m_texture_coords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, float x, float y, float cell_width, float cell_height, float sprite_width, float sprite_height)
	{
		SW_CORE_ASSERT(texture, "Nullptr!");

		glm::vec2 min = { (x * cell_width) / texture->GetWidth(), (y * cell_height) / texture->GetHeight() },
			max = { ((x + sprite_width) * cell_width) / texture->GetWidth(), ((y + sprite_height) * cell_height) / texture->GetHeight() };
		
		return CreateRef<SubTexture2D>(texture, min, max);
	}

	// sprite_size : e.g. { 1, 2 }, will renderer a oblong texture with two quads 
	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cell_size, const glm::vec2& sprite_size)
	{
		return CreateFromCoords(texture, coords.x, coords.y, cell_size.x, cell_size.y, sprite_size.x, sprite_size.y);
	}
}