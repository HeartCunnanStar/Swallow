#pragma once

namespace Swallow{

	class GraphicsContext
  	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		// TODO
		void Create(void* window);
	};
}