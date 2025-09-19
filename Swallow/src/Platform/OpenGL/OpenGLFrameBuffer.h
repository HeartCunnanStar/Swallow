#pragma once

#include "Swallow/Renderer/FrameBuffer.h"

namespace Swallow {

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();
		 
		virtual void Bind() override;
		virtual void Unbind() override;

		virtual FrameBufferSpecification& GetSpecification() override { return m_specification; }
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_specification; }
		virtual uint32_t GetColorAttachment() const override { return m_color_attachment; }

		void Invalidate();
	private:
		uint32_t m_rendererID;
		uint32_t m_color_attachment, m_depth_attachment;
		FrameBufferSpecification m_specification;
	};
}