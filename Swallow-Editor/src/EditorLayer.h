#pragma once

#include <Swallow.h>

namespace Swallow {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(TimeStep time_step) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

	private:
		OrthographicCameraController m_camera_controller;

		Ref<VertexArray> m_squareVA;
		Ref<Shader> m_shader;

		Ref<FrameBuffer> m_frame_buffer;
		Ref<Texture2D> m_test_texture;
		Ref<Texture2D> m_bg_texture;

		glm::vec4 m_square_color = { 0.2f, 0.3f, 0.8f, 1.0f };

		bool m_view_is_focused = false;
		bool m_view_is_hovered = false;

		glm::vec2 m_viewport_size = { 0.f, 0.f };
	};
}