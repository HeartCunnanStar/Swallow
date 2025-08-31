#include "swpch.h"
#include "OrthographicCameraController.h"

#include "Swallow/Core/Input.h"
#include "Swallow/Core/KeyCodes.h"

namespace Swallow {

	OrthographicCameraController::OrthographicCameraController(float aspect_ratio, bool can_rotate)
		: m_aspect_ratio(aspect_ratio), m_camera(-m_aspect_ratio * m_zoom_level, m_aspect_ratio * m_zoom_level, -m_zoom_level, m_zoom_level), m_can_rotate(can_rotate)
	{

	}

	void OrthographicCameraController::OnUpdata(TimeStep time_step)
	{
		if (Swallow::Input::IsKeyDown(SW_KEY_LEFT))
			m_camera_position.x -= m_camera_move_speed * time_step;
		else if (Swallow::Input::IsKeyDown(SW_KEY_RIGHT))
			m_camera_position.x += m_camera_move_speed * time_step;

		if (Swallow::Input::IsKeyDown(SW_KEY_DOWN))
			m_camera_position.y -= m_camera_move_speed * time_step;
		else if (Swallow::Input::IsKeyDown(SW_KEY_UP))
			m_camera_position.y += m_camera_move_speed * time_step;

		if (m_can_rotate)
		{
			if (Swallow::Input::IsKeyDown(SW_KEY_E))
				m_camera_rotation += m_camera_rotation_speed * time_step;
			if (Swallow::Input::IsKeyDown(SW_KEY_Q))
				m_camera_rotation -= m_camera_rotation_speed * time_step;

			m_camera.SetRotation(m_camera_rotation);
		}

		m_camera.SetPosition(m_camera_position);

		// smooth the move
		m_camera_move_speed = m_zoom_level;
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(SW_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(SW_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_zoom_level -= event.GetYOffset() * 0.25f;
		m_zoom_level = m_zoom_level < 0.2f ? 0.2f : m_zoom_level;
		m_camera.SetProjtction(-m_aspect_ratio * m_zoom_level, m_aspect_ratio * m_zoom_level, -m_zoom_level, m_zoom_level);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
	{
		m_aspect_ratio = event.GetWidth() / static_cast<float>(event.GetHeight());
		m_camera.SetProjtction(-m_aspect_ratio * m_zoom_level, m_aspect_ratio * m_zoom_level, -m_zoom_level, m_zoom_level);

		return false;
	}
}