#pragma once

#include "Swallow/Renderer/Buffer.h"

#include <memory>

namespace Swallow {

	class SWALLOW_API VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* CreateIns();
	};
}