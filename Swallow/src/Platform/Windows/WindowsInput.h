#pragma once

#include "Swallow/Core/Input.h"

namespace Swallow{

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyDownImpl (int keycode) override;
		virtual bool IsMouseButtonDownImpl(int button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}