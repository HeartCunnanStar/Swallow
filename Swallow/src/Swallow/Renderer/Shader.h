#pragma once

#include <string>

namespace Swallow {

	class Shader
	{
	public:
		Shader(const std::string& vertex_src, const std::string& fragment_src);
		~Shader();

		void Bind();
		void Unbind();

	private:
		uint32_t m_rendererID = 0;
	};
}