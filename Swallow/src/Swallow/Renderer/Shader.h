#pragma once

#include <string>

#include "glm/glm.hpp"

namespace Swallow {

	class SWALLOW_API Shader
	{
	public:
		Shader(const std::string& vertex_src, const std::string& fragment_src);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4 matrix);

	private:
		uint32_t m_rendererID = 0;
	};
}