#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Swallow {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexd(const std::shared_ptr<VertexArray>& vertex_array) = 0;

		static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}