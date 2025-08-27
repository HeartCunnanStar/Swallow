#pragma once

#include "Swallow/Core.h"
#include "Swallow/Log.h"

#include <stdint.h>

namespace Swallow {
	
	enum class ShaderDataType : uint32_t
	{
		None = 0,
		Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Mat3, Mat4, // mat means matrix (3 * 3) and (4 * 4)
		Bool
	};

	//uint32_t ShaderDataTypeSize(ShaderDataType type);
	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		using SD = ShaderDataType;
		switch (type)
		{
		case SD::Bool:		return 1;
		case SD::Float:		return 4;
		case SD::Float2:	return 4 * 2;
		case SD::Float3:	return 4 * 3;
		case SD::Float4:	return 4 * 4;
		case SD::Int:		return 4;
		case SD::Int2:		return 4 * 2;
		case SD::Int3:		return 4 * 3;
		case SD::Int4:		return 4 * 4;
		case SD::Mat3:		return 4 * 3 * 3;
		case SD::Mat4:		return 4 * 4 * 4;
		}

		SW_CORE_ASSERT(false, "Unknow ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		ShaderDataType type;		
		std::string name;		
		uint32_t offset;
		uint32_t size;
		bool is_normalized;

		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool is_normalized = false)
			: name(name), type(type), size(ShaderDataTypeSize(type)), 
			offset(0), is_normalized(is_normalized) { }

		uint32_t GetComponentCount() const;
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_elements(elements) 
		{
			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_elements; }
		inline uint32_t GetStride() const { return m_stride; }

		// supports range-for 
		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }

	private:
		void CalculateOffsetAndStride();

	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayOut(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}