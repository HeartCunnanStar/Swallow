#pragma once

#include "Swallow/Core.h"
#include "Swallow/Events/Event.h"
#include "Swallow/Core/TimeStep.h"

namespace Swallow {

	class SWALLOW_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {} 
		virtual void OnUpdate(TimeStep time_step) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_debug_name; }

	protected:
		std::string m_debug_name;
	};

}