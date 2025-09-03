#include "swpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Swallow {

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetDepthTest(bool flag)
	{
		if (flag)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::DrawIndexd(const Ref<VertexArray>& vertex_array, uint32_t index_count)
	{
		glDrawElements(GL_TRIANGLES, index_count == 0 ?
			vertex_array->GetIndexBuffer()->GetCount() : index_count, GL_UNSIGNED_INT, nullptr);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			SW_CORE_ERROR("OpenGL error after texture loaid");

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}