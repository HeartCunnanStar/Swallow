#pragma once

#include  "Swallow/Renderer/GraphicsContext.h"

// forward statement (struct, not calss)
struct GLFWwindow;

namespace Swallow {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window_handle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_window_handle;
	};
}