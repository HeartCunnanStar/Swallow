#include <Swallow.h>

class ExampleLayer : public Swallow::Layer
{
public:
	ExampleLayer() : Layer("Layer")
	{
	}

	void OnUpdate() override
	{
		SW_INFO("ExampleLayer::Update");
	}

	void OnEvent(Swallow::Event& event) override
	{
		SW_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public Swallow::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushLayer(new Swallow::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Swallow::Application* Swallow::CreateApplication()
{
	return new Sandbox();
}