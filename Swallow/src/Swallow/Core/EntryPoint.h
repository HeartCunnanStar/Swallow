#pragma once

#ifdef SW_PLATFORMS_WINDOWS
	
extern Swallow::Application* Swallow::CreateApplication();

int main(int argc, char** argv)
{
	Swallow::Log::Init();
	SW_CORE_WARN("Initialized Log!");
	SW_INFO("Hello?");

	SW_PROFILE_BEGIN_SESSION("Startup", "SwallowProfile-Startup.json");
	auto app = Swallow::CreateApplication();
	SW_PROFILE_END_SESSION();

	SW_PROFILE_BEGIN_SESSION("Runtime", "SwallowProfile-Runtime.json");
	app->Run();
	SW_PROFILE_END_SESSION();

	SW_PROFILE_BEGIN_SESSION("Shutdown","SwallowProfile-Shutdown.json");
	delete app;
	SW_PROFILE_END_SESSION();
}

#endif