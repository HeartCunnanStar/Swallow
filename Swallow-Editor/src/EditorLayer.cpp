#include "EditorLayer.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include <chrono>

namespace Swallow {

	EditorLayer::EditorLayer() :
		Layer("EditorLayer"),
		m_camera_controller(1280.f / 720.f, true),
		m_viewport_size(1280.0f, 720.0f)
	{

	}

	void EditorLayer::OnAttach()
	{
		SW_PROFILE_FUNCTION();

		m_test_texture = Texture2D::CreateIns("assets/textures/kita_test.png");
		m_bg_texture = Texture2D::CreateIns("assets/textures/checkboard.png");
		//m_some_ele = SubTexture2D::CreateFromCoords(m_sprite_sheet, {}, {});

		// build frame buffer
		FrameBufferSpecification FB_spec;
		FB_spec.width = 1280;
		FB_spec.height = 720;
		m_frame_buffer = FrameBuffer::Create(FB_spec);

		m_active_scene = CreateRef<Scene>();

		// create entity
		auto square = m_active_scene->CreateEntity("Default square");
		square.AddComponent<SpriteRendererComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

		m_square_entity = square;

		m_camera_entity = m_active_scene->CreateEntity("Camera entity A");
		m_camera_entity.AddComponent<CameraComponent>();

		m_camera_test_entity = m_active_scene->CreateEntity("Camera entity B");
		auto& temp = m_camera_test_entity.AddComponent<CameraComponent>();
		temp.is_primary = false;
	}

	void EditorLayer::OnDetach()
	{
		SW_PROFILE_FUNCTION();

	}

	void EditorLayer::OnUpdate(TimeStep time_step)
	{
		SW_PROFILE_FUNCTION();

		//------------Resize---------------------
		FrameBufferSpecification& spec = m_frame_buffer->GetSpecification();
		if ( m_viewport_size.x > 0 && m_viewport_size.y > 0 &&
			(!IsEqual(spec.width, m_viewport_size.x) || !IsEqual(spec.height, m_viewport_size.y)))
		{
			m_frame_buffer->Resize(static_cast<uint32_t>(m_viewport_size.x), static_cast<uint32_t>(m_viewport_size.y));
			m_camera_controller.OnResize(m_viewport_size.x, m_viewport_size.y);
			m_active_scene->OnViewportResize(static_cast<uint32_t>(m_viewport_size.x), static_cast<uint32_t>(m_viewport_size.y));
		}

		//--------------Updata-------------------
		//Timer timer("EditorLayer::Onupdate", [&](auto performance_data) {m_porformance_result.push_back(performance_data)});
		if (m_is_view_focused)
			m_camera_controller.OnUpdata(time_step);


		//--------------Render-------------------
		Renderer2D::ResetStats();
		{
			SW_PROFILE_SCOPE("Render-pre");
			m_frame_buffer->Bind();
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();
		}

		{
			SW_PROFILE_SCOPE("Render-draw");

			//Update-Scene
			m_active_scene->OnUpdate(time_step);
		}

		m_frame_buffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		SW_PROFILE_FUNCTION();

		static bool docking_is_enabled = true;
		if (docking_is_enabled)
		{
			static bool dockspace_is_opened = true;
			static bool opt_is_fullscreen_persistent = true;
			bool opt_is_fullscreen = opt_is_fullscreen_persistent;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_is_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &dockspace_is_opened, window_flags);
			ImGui::PopStyleVar();

			if (opt_is_fullscreen)
				ImGui::PopStyleVar(2);

			// Dockspace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Exit"))
						Application::GetIns().Close();
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			ImGui::Begin("Settings");
			ImGui::SetWindowFontScale(1.25f);

			auto status = Renderer2D::GetStats();
			ImGui::Text("Renderer2D Stats");
			ImGui::Text("Draw Calls: %d", status.DrawCalls);
			ImGui::Text("Quads:      %d", status.QuadCount);
			ImGui::Text("Vertices:   %d", status.GetTotalVertexCount());
			ImGui::Text("Indices:    %d", status.GetTotalIndexCount());

			ImGui::Separator();

			ImGui::Text("Viewport Info");
			ImGui::Text("Viewport Size: %.1f x %.1f", m_viewport_size.x, m_viewport_size.y);
			ImGui::Text("FrameBuffer ID: %d", m_frame_buffer->GetColorAttachment());
			ImGui::Text("View Focused: %s", m_is_view_focused ? "Yes" : "No");
			ImGui::Text("View Hovered: %s", m_is_view_hovered ? "Yes" : "No");

			if (m_square_entity)
			{
				ImGui::Separator();
				auto& tag = m_square_entity.GetComponent<TagComponent>().tag;
				ImGui::Text(tag.c_str());
				auto& square_color = m_square_entity.GetComponent<SpriteRendererComponent>().color;
				ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color));
				ImGui::Separator();
			}

			// control camera transform
			ImGui::DragFloat3("Camera Transform", glm::value_ptr(m_camera_entity.GetComponent<TransformComponent>().transform[3]));
			
			if (ImGui::Checkbox("Camera A", &m_camera_switch))
			{
				m_camera_entity.GetComponent<CameraComponent>().is_primary = m_camera_switch;
				m_camera_test_entity.GetComponent<CameraComponent>().is_primary = !m_camera_switch;
			}

			{
				auto& camera = m_camera_test_entity.GetComponent<CameraComponent>().camera;
				float size = camera.GetOrthographicSize();
				if (ImGui::DragFloat("Camera B Orthographic Size", &size))
					camera.SetOrthographicSize(size);
			}


			ImGui::End();

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
			ImGui::Begin("Viewport");

			// only when Focused && Hovered will convet events 
			m_is_view_focused = ImGui::IsWindowFocused();
			m_is_view_hovered = ImGui::IsWindowHovered();
			Application::GetIns().GetImGuiLayer()->SetBlockEvents(!(m_is_view_focused && m_is_view_hovered));

			// get widget's panel size from ImGui
			ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
			m_viewport_size = { viewport_panel_size.x, viewport_panel_size.y };

			uint32_t textureID = m_frame_buffer->GetColorAttachment();
			ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2(m_viewport_size.x, m_viewport_size.y), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::End();
			ImGui::PopStyleVar();

			ImGui::End();
		}
		else
		{
			ImGui::Begin("Settings");

			auto status = Renderer2D::GetStats();
			ImGui::Text("Renderer2D Stats");
			ImGui::Text("Draw Calls: %d", status.DrawCalls);
			ImGui::Text("Quads:      %d", status.QuadCount);
			ImGui::Text("Vertices:   %d", status.GetTotalVertexCount());
			ImGui::Text("Indices:    %d", status.GetTotalIndexCount());
			//for (auto& result : m_performance_result)
			//{
			//	char label_buffer[64];
			//	strcpy(label_buffer, result.name);
			//	strcat(label_buffer, " %.3fms");
			//	ImGui::Text(label_buffer, result.time);
			//}
			//m_performance_result.clear();

			ImGui::ColorEdit4("Square Color", glm::value_ptr(m_square_color));
			//ImGui::Image(reinterpret_cast<void*>(m_bg_texture->GetRendererID()), ImVec2(64.f, 64.f));
			ImGui::Image(reinterpret_cast<void*>(m_frame_buffer->GetColorAttachment()), ImVec2(1280.f, 720.f), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::End();
		}
	}

	void EditorLayer::OnEvent(Event& event)
	{
		m_camera_controller.OnEvent(event);
	}
}