#pragma once

#include "Swallow/Core/Core.h"

namespace Swallow {

	class SWALLOW_API Input
	{
	public:
		static bool IsKeyDown(int keycode);
		static bool IsMouseButtonDown(int button);
		static float GetMouseX();
		static float GetMouseY();
		static std::pair<float, float> GetMousePos();

	};

	//class SWALLOW_API Input
	//{
	//public:
	//	inline static bool IsKeyDown(int keycode) { return s_instance->IsKeyDownImpl(keycode); }
	//	inline static bool IsMouseButtonDown(int button) { return s_instance->IsMouseButtonDownImpl(button); }
	//	inline static float GetMouseX() { return s_instance->GetMouseXImpl(); }
	//	inline static float GetMouseY() { return s_instance->GetMouseYImpl(); }
	//	inline static std::pair<float, float> GetMousePos() { return s_instance->GetMousePosImpl(); }

	//protected:
	//	virtual bool IsKeyDownImpl(int keycode) = 0;
	//	virtual bool IsMouseButtonDownImpl(int button) = 0;
	//	virtual std::pair<float, float> GetMousePosImpl() = 0;
	//	virtual float GetMouseXImpl() = 0;
	//	virtual float GetMouseYImpl() = 0;

	//private:
	//	static Input* s_instance;
	//};
}