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

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual FrameBufferSpecification& GetSpecification() override { return m_specification; }
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_specification; }
		virtual uint32_t GetColorAttachment() const override { return m_color_attachment; }

		void Invalidate();
	private:
		uint32_t m_rendererID = 0;
		uint32_t m_color_attachment = 0;
		uint32_t m_depth_attachment = 0;
		FrameBufferSpecification m_specification;
	};
}