#include "swpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Swallow {

	Ref<VertexArray> VertexArray::CreateIns()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexArray>(); break;
		case RendererAPI::API::None:	SW_CORE_ASSERT(false, "RendererAPI is none!"); break;
		}

		SW_CORE_ASSERT(false, "Unknown chosen API!");
		return nullptr;
	}
}