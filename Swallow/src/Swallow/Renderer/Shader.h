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

		static Shader* CreateIns(const std::string& vertex_src, const std::string& fragment_src);
	};
}