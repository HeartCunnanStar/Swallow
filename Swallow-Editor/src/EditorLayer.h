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

		Ref<Scene> m_active_scene;
		Entity m_square_entity;
		Entity m_camera_entity;
		Entity m_camera_test_entity;

		bool m_camera_switch = true;

		// in the scene

		Ref<VertexArray> m_squareVA;
		Ref<Shader> m_shader;

		Ref<FrameBuffer> m_frame_buffer;
		Ref<Texture2D> m_test_texture;
		Ref<Texture2D> m_bg_texture;

		glm::vec4 m_square_color = { 0.2f, 0.3f, 0.8f, 1.0f };

		// 

		bool m_is_view_focused = false;
		bool m_is_view_hovered = false;

		glm::vec2 m_viewport_size = { 0.f, 0.f };
	};
}