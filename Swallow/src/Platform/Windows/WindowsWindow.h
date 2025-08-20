#pragma once

#include "Swallow/Window.h"

#include <GLFW/glfw3.h>

namespace Swallow {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_data.width; }
		inline unsigned int GetHeight() const override { return m_data.height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_data.event_callback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_window;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool is_vertical_sync;

			EventCallbackFn event_callback;
		};

		WindowData m_data;
	};

}
