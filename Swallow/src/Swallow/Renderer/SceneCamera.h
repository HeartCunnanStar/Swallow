#pragma once

#include "Swallow/Renderer/Camera.h"

namespace Swallow {

	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float near_clip, float far_clip);
		void SetViewportSize(uint32_t width, uint32_t height);

		float GetOrthographicSize() const { return m_orthographic_size; }
		void SetOrthographicSize(float size) { m_orthographic_size = size; RecalculateProjection(); }

	private:
		void RecalculateProjection();

	private:
		float m_orthographic_size = 10.f,
			m_orthgoraphic_near_clip = -1.f,
			m_orthgoraphic_far_clip = 1.f;
		float m_aspect_ratio = 0.f;
	};

}