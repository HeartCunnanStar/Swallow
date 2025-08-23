#include <Swallow.h>

class ExampleLayer : public Swallow::Layer
{
public:
	ExampleLayer() : Layer("Layer")
	{
	}

	void OnUpdate() override
	{
		// SW for DEBUG
		//SW_INFO("ExampleLayer::Update");

		// SW for DEBUG
		if (Swallow::Input::IsKeyDown(SW_KEY_TAB))
			SW_TRACE("Key TAB is down (poll)");
	}

	void OnEvent(Swallow::Event& event)  override
	{
		// SW for DEBUG
		//SW_TRACE("{0}", event.ToString());

		// SW for DEBUG
		if (event.GetEventType() == Swallow::EventType::KeyDown)
		{
			Swallow::KeyDownEvent& e = static_cast<Swallow::KeyDownEvent&>(event);
			if (e.GetKeyCode() == SW_KEY_TAB)
				SW_TRACE("Key TAB is down (event)");
			else
				SW_TRACE("{0}", static_cast<char>(e.GetKeyCode()));
			
		}
	}
};

class Sandbox : public Swallow::Application
{
public: 
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new Swallow::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Swallow::Application* Swallow::CreateApplication()
{
	return new Sandbox();
}