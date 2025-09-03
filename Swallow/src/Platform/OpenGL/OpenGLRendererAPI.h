#pragma once

#include "Swallow/Renderer/RendererAPI.h"

namespace Swallow {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void Clear() override;

		virtual void DrawIndexd(const Ref<VertexArray>& vertex_array) override;
	};
}