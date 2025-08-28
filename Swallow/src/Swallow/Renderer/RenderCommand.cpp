#include "swpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Swallow {

	RendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI();
}