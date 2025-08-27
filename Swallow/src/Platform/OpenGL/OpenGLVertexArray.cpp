#include "swpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Swallow {

	static GLenum ShaderDataType2OpenGLType(ShaderDataType type)
	{
		using SD = ShaderDataType;
		switch (type)
		{
		case SD::Bool:		return GL_BOOL;
		case SD::Float:
		case SD::Float2:
		case SD::Float3:
		case SD::Float4:	return GL_FLOAT;
		case SD::Int:
		case SD::Int2:
		case SD::Int3:
		case SD::Int4:		return GL_INT;
		case SD::Mat3:
		case SD::Mat4:		return GL_FLOAT;
		}

		SW_CORE_ASSERT(false, "Unknow ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_rendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_rendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer)
	{
		glBindVertexArray(m_rendererID);
		vertex_buffer->Bind();

		SW_CORE_ASSERT(vertex_buffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		uint32_t index = 0; 
		for (const auto& ele : vertex_buffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, ele.GetComponentCount(),
				ShaderDataType2OpenGLType(ele.type),
				ele.is_normalized ? GL_TRUE : GL_FALSE,
				vertex_buffer->GetLayout().GetStride(),
				reinterpret_cast<const void*>(ele.offset));
			++index;  
		}

		m_vertex_buffers.push_back(vertex_buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer)
	{
		glBindVertexArray(m_rendererID);
		index_buffer->Bind();

		m_index_buffer = index_buffer;
	}

}