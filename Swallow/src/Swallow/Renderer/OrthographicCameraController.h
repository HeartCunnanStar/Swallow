#pragma once

#include "OrthographicCamera.h"

#include "Swallow/Core/TimeStep.h"
#include "Swallow/Events/ApplicationEvent.h"
#include "Swallow/Events/MouseEvent.h"

namespace Swallow {

	class SWALLOW_API OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspect_ratio, bool can_rotate = false);

		void OnUpdata(TimeStep time_step);
		void OnEvent(Event& event);

		OrthographicCamera& GerCamera() { return m_camera; }
		const OrthographicCamera& GerCamera() const { return m_camera; }

		void SetZoomLevel(float level) { m_zoom_level = level; }
		float GetZoomLevel() const { return m_zoom_level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);

	private:
		float m_aspect_ratio;
		float m_zoom_level = 1.0f;

		bool m_can_rotate;
		float m_camera_rotation = 0.0f;
		float m_camera_move_speed = 1.0f, m_camera_rotation_speed = 20.0f;
		glm::vec3 m_camera_position = { 0.0f, 0.0f, 0.0f };

		OrthographicCamera m_camera;
	};
}