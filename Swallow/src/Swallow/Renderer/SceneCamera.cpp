#include "swpch.h"

#include <glm/gtc/matrix_transform.hpp>

#include "SceneCamera.h"

namespace Swallow {

	SceneCamera::SceneCamera()
	{

	}

	void SceneCamera::SetOrthographic(float size, float near_clip, float far_clip)
	{
		m_orthographic_size = size;
		m_orthgoraphic_far_clip = far_clip;
		m_orthgoraphic_near_clip = near_clip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		float ortho_left = -m_orthographic_size * m_aspect_ratio * 0.5f;
		float ortho_right = m_orthographic_size * m_aspect_ratio * 0.5f;
		float ortho_bottom = -m_orthographic_size * 0.5f;
		float ortho_top = m_orthographic_size * 0.5f;

		m_projection_matrix = glm::ortho(
			ortho_left, ortho_right, ortho_bottom, ortho_top,
			m_orthgoraphic_near_clip, m_orthgoraphic_far_clip
		);
	}

};

