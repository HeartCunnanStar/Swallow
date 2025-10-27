#include <Swallow.h>
#include <Swallow/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Swallow
{
	class SwallowEditor : public Application
	{
	public:
		SwallowEditor() : Application("Swallow Editor")
		{
			PushLayer(new EditorLayer());
		}

		~SwallowEditor()
		{

		}
	};

	Swallow::Application* Swallow::CreateApplication()
	{
		return new SwallowEditor();
	}
}