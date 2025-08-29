#pragma once

#include "Swallow/Core/Core.h"
#include "Swallow/Renderer/Shader.h"

#include <string>
#include <glm/glm.hpp>

namespace Swallow {

	class SWALLOW_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertex_src, const std::string& fragment_src);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformMat3(const std::string& name, const glm::mat3 matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4 matrix);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2 value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3 value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4 value);

		void UploadUniformInt(const std::string& name, int value);
		//void UploadUniformInt2(const std::string& name, const glm::vec4 value);
		//void UploadUniformInt3(const std::string& name, const glm::vec4 value);
		//void UploadUniformInt4(const std::string& name, const glm::vec4 value);

	private:
		uint32_t m_rendererID = 0;
	};
}