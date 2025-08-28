#pragma once

#include "Swallow/Renderer/RendererAPI.h"

namespace Swallow {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexd(const std::shared_ptr<VertexArray>& vertex_array) override;
	};
}