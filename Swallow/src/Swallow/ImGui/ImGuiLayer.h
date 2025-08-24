#pragma once

#include "Swallow/Layer.h"

#include "Swallow/Events/MouseEvent.h"
#include "Swallow/Events/ApplicationEvent.h"
#include "Swallow/Events/KeyEvent.h"

namespace Swallow {

	class SWALLOW_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		//virtual void OnUpdate() override;

		virtual void OnDetach() override;
		virtual void OnAttach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_time = 0.0f;
	};

	// before 250823
	//class SWALLOW_API ImGuiLayer : public Layer
	//{
	//public:
	//	ImGuiLayer();
	//	~ImGuiLayer();

	//	void OnAttach();
	//	void OnDetach();
	//	void OnUpdate();
	//	void OnEvent(Event& event);

	//private:
	//	bool OnMouseButtonDownEvent(MouseButtonDownEvent& event);
	//	bool OnMouseButtonUpEvent(MouseButtonUpEvent& event);
	//	bool OnMouseScrolledEvent(MouseScrolledEvent& event);
	//	bool OnMouseMovedEvent(MouseMovedEvent& event);

	//	bool OnKeyDownEvent(KeyDownEvent& event);
	//	bool OnKeyUpEvent(KeyUpEvent& event);
	//	bool OnKeyTypedEvent(KeyTypedEvent& event);

	//	bool OnWindowResizeEvent(WindowResizeEvent& event);

	//private:
	//	float m_time = 0.0f;
	//};

}