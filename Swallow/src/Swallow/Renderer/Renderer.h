#pragma once

namespace Swallow {

	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_rendererAPI; }
	private:
		static RendererAPI s_rendererAPI;
	};
}