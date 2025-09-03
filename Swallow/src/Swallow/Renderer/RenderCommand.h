#pragma once

#include "RendererAPI.h"

namespace Swallow {

	class RenderCommand
	{
	public:
		inline static void Init() { s_rendererAPI->Init(); }
		inline static void SetClearColor(const glm::vec4& color) { s_rendererAPI->SetClearColor(color); }
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_rendererAPI->SetViewport(x, y, width, height); }
		inline static void Clear() { s_rendererAPI->Clear(); }
		inline static void DrawIndexd(const Ref<VertexArray>& vertex_array, uint32_t count = 0) { s_rendererAPI->DrawIndexd(vertex_array, count); }
		inline static void SetDepthTest(bool flag) { s_rendererAPI->SetDepthTest(flag); }

	private:
		static RendererAPI* s_rendererAPI;
	};
}