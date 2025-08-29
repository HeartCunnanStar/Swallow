#include "swpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Swallow {
	
	Shader* Shader::CreateIns(const std::string& vertex_src, const std::string& fragment_src)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return new OpenGLShader(vertex_src, fragment_src); break;
		case RendererAPI::API::None:	SW_CORE_ASSERT(false, "RendererAPI is none!"); break;
		}

		SW_CORE_ASSERT(false, "Unknown chosen API!");
		return nullptr;
	}
}