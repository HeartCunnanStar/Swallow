#pragma once

#include <string>

namespace Swallow {

	class SWALLOW_API Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> CreateIns(const std::string& path); // use file name as defualt
		static Ref<Shader> CreateIns(const std::string& name, const std::string& vertex_src, const std::string& fragment_src);
	};

	class SWALLOW_API ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load( const std::string& path); // use file name as defualt
		Ref<Shader> Load(const std::string& name, const std::string& path);

		Ref<Shader> Get(const std::string& name);

	private:
		bool CheckIfHave(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_shaders;
	};
}