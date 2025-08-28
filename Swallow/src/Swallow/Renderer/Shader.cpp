#include "swpch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Swallow {

	Shader::Shader(const std::string& vertex_src, const std::string& fragment_src)
	{
		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = vertex_src.c_str();
		glShaderSource(vertex_shader, 1, &source, 0); // send vertex's source code to GL

		glCompileShader(vertex_shader);

		GLint is_compiled = 0;
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled);
		// when isn't compiled
		if (is_compiled == GL_FALSE) 
		{
			GLint max_length = 0;
			glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length); // get log length(inlcude NULL)

			std::vector<GLchar> info_log(max_length);
			glGetShaderInfoLog(vertex_shader, max_length, &max_length, &info_log[0]); // get debug info (log)

			glDeleteShader(vertex_shader);

			SW_CORE_ERROR("{0}", info_log.data());			
			SW_CORE_ASSERT(false, "Vertex shader compilation failure!");

			return;
		}
		
		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragment_src.c_str();
		glShaderSource(fragment_shader, 1, &source, 0); // send fragment's source code to GL

		glCompileShader(fragment_shader);

		is_compiled = 0;
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled);
		// when isn't compiled
		if (is_compiled == GL_FALSE) 
		{
			GLint max_length = 0;
			glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length); // get log length(inlcude NULL)

			std::vector<GLchar> info_log(max_length);
			glGetShaderInfoLog(fragment_shader, max_length, &max_length, &info_log[0]); // get debug info (log)

			glDeleteShader(fragment_shader);

			SW_CORE_ERROR("{0}", info_log.data());
			SW_CORE_ASSERT(false, "Fragment shader compilation failure!");

			return;
		}

		m_rendererID = glCreateProgram();

		glAttachShader(m_rendererID, vertex_shader);
		glAttachShader(m_rendererID, fragment_shader);

		glLinkProgram(m_rendererID);
		GLint is_linked = 0;
		glGetProgramiv(m_rendererID, GL_LINK_STATUS, reinterpret_cast<int*>(&is_linked));
		//when links wrong	
		if (is_linked == GL_FALSE)
		{
			GLint max_length = 0;
			glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &max_length); // get log length(inlcude NULL)

			std::vector<GLchar> info_log(max_length);
			glGetShaderInfoLog(m_rendererID, max_length, &max_length, &info_log[0]); // get debug info (log)

			glDeleteProgram(m_rendererID);
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);

			SW_CORE_ERROR("{0}", info_log.data());
			SW_CORE_ASSERT(false, "Shader link failure!");

			return;
		}

		glDetachShader(m_rendererID, vertex_shader);
		glDetachShader(m_rendererID, fragment_shader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_rendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_rendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	} 

	// upload uniform matrix to the shader
	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4 matrix)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}


}