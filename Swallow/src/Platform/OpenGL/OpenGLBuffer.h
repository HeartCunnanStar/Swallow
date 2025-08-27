#pragma once

#include "Swallow/Renderer/Buffer.h"

namespace Swallow {
	 
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayOut(const BufferLayout& layout) override { m_layout = layout; }
		virtual const BufferLayout& GetLayout() const override {return m_layout; }

	private:
		uint32_t m_rendererID = 0;
		BufferLayout m_layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_count; }

	private:
		uint32_t m_rendererID = 0;
		uint32_t m_count;
	};
}