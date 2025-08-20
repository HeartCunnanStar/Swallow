#pragma once

#ifdef SW_PLATFORMS_WINDOWS
	
extern Swallow::Application* Swallow::CreateApplication();

int main(int argc, char** argv)
{
	Swallow::Log::Init();
	SW_CORE_WARN("Initialized Log!");
	SW_INFO("Hello?");

	auto app = Swallow::CreateApplication();
	app->run();
	delete app;
}

#endif