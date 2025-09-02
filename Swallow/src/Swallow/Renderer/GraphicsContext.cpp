#include "swpch.h"

#include "GraphicsContext.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Swallow {

	Scope<GraphicsContext> GraphicsContext::CreateIns(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window)); break;
		case RendererAPI::API::None:	SW_CORE_ASSERT(false, "RendererAPI is none!"); break;
		}

		SW_CORE_ASSERT(false, "Unknown chosen API!");
		return nullptr;
	}
}