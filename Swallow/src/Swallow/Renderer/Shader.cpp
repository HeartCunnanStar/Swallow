#include "swpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Swallow {

	Ref<Shader> Shader::CreateIns(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(path); break;
		case RendererAPI::API::None:	SW_CORE_ASSERT(false, "RendererAPI is none!"); break;
		}

		SW_CORE_ASSERT(false, "Unknown chosen API!");
		return nullptr;
	}

	Ref<Shader> Shader::CreateIns(const std::string& name, const std::string& vertex_src, const std::string& fragment_src)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(name, vertex_src, fragment_src); break;
		case RendererAPI::API::None:	SW_CORE_ASSERT(false, "RendererAPI is none!"); break;
		}

		SW_CORE_ASSERT(false, "Unknown chosen API!");
		return nullptr;
	}

	//-------------ShaderLibrary-----------------------

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		const auto& name = shader->GetName();
		SW_CORE_ASSERT(!CheckIfHave(name), "Shader already exists!");
		m_shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		SW_CORE_ASSERT(!CheckIfHave(name), "Shader already exists!");
		m_shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& path)
	{
		auto shader = Shader::CreateIns(path);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path)
	{
		auto shader = Shader::CreateIns(path);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		SW_CORE_ASSERT(CheckIfHave(name), "Shader already exists!");
		return m_shaders[name];
	}

	bool ShaderLibrary::CheckIfHave(const std::string& name) const
	{
		return m_shaders.find(name) != m_shaders.end();
	}
}