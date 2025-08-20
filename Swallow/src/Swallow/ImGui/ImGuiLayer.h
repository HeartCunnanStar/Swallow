#pragma once

#include "Swallow/Layer.h"

namespace Swallow {

	class SWALLOW_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		float m_time = 0.0f;
	};

}