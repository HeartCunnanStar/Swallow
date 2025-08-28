#include "swpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Swallow {

	//uint32_t ShaderDataTypeSize(ShaderDataType type)
	//{
	//	using SD = ShaderDataType;
	//	switch (type)
	//	{
	//	case SD::Bool:		return 1;
	//	case SD::Float:		return 4;
	//	case SD::Float2:	return 4 * 2;
	//	case SD::Float3:	return 4 * 3;
	//	case SD::Float4:	return 4 * 4;
	//	case SD::Int:		return 4;
	//	case SD::Int2:		return 4 * 2;
	//	case SD::Int3:		return 4 * 3;
	//	case SD::Int4:		return 4 * 4;
	//	case SD::Mat3:		return 4 * 3 * 3;
	//	case SD::Mat4:		return 4 * 4 * 4;
	//	}
	//	SW_CORE_ASSERT(false, "Unknow ShaderDataType!");
	//	return 0;
	//}

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{		
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size); break;
		case RendererAPI::API::None: SW_CORE_ASSERT(false, "RendererAPI is none!"); break;
		}

		SW_CORE_ASSERT(false, "Unknown choosen API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count); break;
		case RendererAPI::API::None: SW_CORE_ASSERT(false, "RendererAPI is none!"); break;
		}

		SW_CORE_ASSERT(false, "Unknown choosen API!");
		return nullptr;
	}

	uint32_t BufferElement::GetComponentCount() const
	{
		using SD = ShaderDataType;
		switch (type)
		{
		case SD::Bool:		return 1;
		case SD::Float:		return 1;
		case SD::Float2:	return 2;
		case SD::Float3:	return 3;
		case SD::Float4:	return 4;
		case SD::Int:		return 1;
		case SD::Int2:		return 2;
		case SD::Int3:		return 3;
		case SD::Int4:		return 4;
		case SD::Mat3:		return 3 * 3;
		case SD::Mat4:		return 4 * 4;
		}

		SW_CORE_ASSERT(false, "Unknow ShaderDataType!");
		return 0;
	}

	void BufferLayout::CalculateOffsetAndStride()
	{
		uint32_t offset = 0;
		m_stride = 0;
		for (auto& ele : m_elements)
		{
			ele.offset = offset;
			offset += ele.size;
			m_stride += ele.size;
		}
	}
}

