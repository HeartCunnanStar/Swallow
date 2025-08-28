#pragma once

#include "Swallow/Renderer/VertexArray.h"

namespace Swallow {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const override { return m_vertex_buffers; };
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_index_buffer; };

	private:
		uint32_t m_rendererID = 0;

		std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
		std::shared_ptr<IndexBuffer> m_index_buffer;
	};
}