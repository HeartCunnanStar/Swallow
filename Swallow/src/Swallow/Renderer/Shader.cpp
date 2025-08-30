#include "swpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Swallow {

	Ref<Shader> Shader::CreateIns(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(path); break;
		case RendererAPI::API::None:	SW_CORE_ASSERT(false, "RendererAPI is none!"); break;
		}

		SW_CORE_ASSERT(false, "Unknown chosen API!");
		return nullptr;
	}

	Ref<Shader> Shader::CreateIns(const std::string& vertex_src, const std::string& fragment_src)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(vertex_src, fragment_src); break;
		case RendererAPI::API::None:	SW_CORE_ASSERT(false, "RendererAPI is none!"); break;
		}

		SW_CORE_ASSERT(false, "Unknown chosen API!");
		return nullptr;
	}
}