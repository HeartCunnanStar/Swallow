#include "swpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>

namespace Swallow {

	static GLenum GetShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		else if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
		
		SW_CORE_ASSERT(false, "Invalid shader type!");
		return GL_NONE;
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex_src, const std::string& fragment_src)
		: m_name(name)
	{
		SW_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shader_srcs;
		shader_srcs[GL_VERTEX_SHADER] = vertex_src;
		shader_srcs[GL_FRAGMENT_SHADER] = fragment_src;
		Compile(shader_srcs);
	}

	OpenGLShader::OpenGLShader(const std::string& path)
	{		
		SW_PROFILE_FUNCTION();

		// extract name from path
		// can deal with belows:
		//  renderer/Texture.glsl assests\renderer\texture texture.part1.glsl 
		auto last_slash = path.find_last_of("/\\");
		last_slash = last_slash == std::string::npos ? 0 : last_slash + 1;
		auto last_dot = path.rfind('.');

		auto count = last_dot == std::string::npos ? 
			path.size() - last_slash : last_dot - last_slash;

		m_name = path.substr(last_slash, count);

		std::string src = ReadFile(path);
		auto shader_srcs = PreProcess(src);
		Compile(shader_srcs);
	}

	OpenGLShader::~OpenGLShader()
	{
		SW_PROFILE_FUNCTION();

		glDeleteProgram(m_rendererID);
	}

	void OpenGLShader::Bind() const
	{
		SW_PROFILE_FUNCTION();

		glUseProgram(m_rendererID);
	}

	void OpenGLShader::Unbind() const
	{
		SW_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		SW_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		SW_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2 value)
	{
		SW_PROFILE_FUNCTION();

		UploadUniformFloat2(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3 value)
	{
		SW_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4 value)
	{
		SW_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4 value)
	{
		SW_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}

	// upload uniform matrix3 to the shader
	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3 matrix)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	// upload uniform matrix4 to the shader
	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4 matrix)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	// upload uniform float to the shader
	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform1f(location, value);
	}
	// upload uniform float to the shader
	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2 value)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}
	// upload uniform float3 to the shader
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3 value)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	// upload uniform float4 to the shader
	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4 value)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	// upload uniform int to the shader
	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform1i(location, value);
	}

	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		SW_PROFILE_FUNCTION();

		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (!in.is_open())
		{
			SW_CORE_ERROR("File '{0}' didn't open", path);
			return "";
		}

		in.seekg(0, std::ios::end);
		std::streamsize size = in.tellg();
		in.seekg(0, std::ios::beg);

		if (size <= 0)
		{
			SW_CORE_ERROR("File '{0}' empty or invalid: ", path);
			in.close();
			return "";
		}

		std::string result;
		result.resize(static_cast<size_t>(size));
		in.read(&result[0], size);
		in.close();

		//in.seekg(0, std::ios::end);

		//std::string result;
		//result.resize(in.tellg());
		//in.seekg(0, std::ios::beg);

		//in.read(&result[0], result.size());
		//in.close();

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& src)
	{
		SW_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shader_srcs;

		const char* type_token = "#type";
		size_t type_token_length = strlen(type_token);
		size_t pos = src.find(type_token, 0);

		while (pos != std::string::npos)
		{
			size_t eol = src.find_first_of("\r\n", pos);
			SW_CORE_ASSERT(eol != std::string::npos, "Syntax error!");

			// get the shader type
			size_t begin = pos + type_token_length + 1;
			std::string type = src.substr(begin, eol - begin);
			SW_CORE_ASSERT(GetShaderTypeFromString(type), "Invalid shader type!");

			// try to find the next type token
			size_t next_line_pos = src.find_first_not_of("\r\n", eol);
			pos = src.find(type_token, next_line_pos);

			// get the whole shader source
			shader_srcs[GetShaderTypeFromString(type)] = src.substr(next_line_pos,
				pos - (next_line_pos == std::string::npos ? src.size() - 1 : next_line_pos));
		}

		return shader_srcs;
	}
	
	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shader_srcs)
	{
		SW_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();

		SW_CORE_ASSERT(shader_srcs.size() <= 2, "Only supports 2 shaders now!");
		std::array<GLuint, 2> compiled_shaders;
		int compiled_shader_idx = 0;
		//std::vector<GLuint> compiled_shaders;
		//compiled_shaders.reserve(shader_srcs.size());

		for (auto& kv : shader_srcs)
		{
			GLenum type = kv.first;
			const std::string& src = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* source = src.c_str();
			glShaderSource(shader, 1, &source, 0); // send shader's source code to GL

			glCompileShader(shader);

			GLint is_compiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);

			// when isn't compiled
			if (is_compiled == GL_FALSE)
			{
				GLint max_length = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length); // get log length(inlcude NULL)

				std::vector<GLchar> info_log(max_length);
				glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]); // get debug info (log)

				glDeleteShader(shader);
				for (auto& t_shader : compiled_shaders)
					glDeleteShader(t_shader);
				glDeleteProgram(program);

				SW_CORE_ERROR("{0}", info_log.data());
				SW_CORE_ASSERT(false, "Shader compilation failure!");

				break;
			}

			glAttachShader(program, shader);
			compiled_shaders[compiled_shader_idx++] = shader;
			//compiled_shaders.push_back(shader);
		}

		glLinkProgram(program);
		GLint is_linked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, reinterpret_cast<int*>(&is_linked));

		//when links wrong	
		if (is_linked == GL_FALSE)
		{
			GLint max_length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length); // get log length(inlcude NULL)

			if (max_length > 0) // if have log
			{
				std::vector<GLchar> info_log(max_length);
				glGetProgramInfoLog(program, max_length, &max_length, &info_log[0]); // get debug info (log)
				SW_CORE_ERROR("{0}", info_log.data());
			}

			glDeleteProgram(program);

			for (auto& t_shader : compiled_shaders)
				glDeleteShader(t_shader);

			SW_CORE_ASSERT(false, "Shader links failure!");

			return;
		}

		for (auto& t_shader : compiled_shaders)
			glDeleteShader(t_shader);
		
		m_rendererID = program;
	}
}		
