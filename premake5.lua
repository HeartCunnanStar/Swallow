workspace "Swallow"
	architecture "x64"

	startproject "sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

filter "system:windows"
	buildoptions 
	{
		"/utf-8"
	}
    
-- include dir relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Swallow/third_party/GLFW/include"
IncludeDir["Glad"] = "Swallow/third_party/Glad/include"
IncludeDir["ImGui"] = "Swallow/third_party/imgui"
IncludeDir["glm"] = "Swallow/third_party/glm"

include "Swallow/third_party/GLFW"
include "Swallow/third_party/Glad"
include "Swallow/third_party/imgui"

project "Swallow"
	location "Swallow"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "swpch.h"
	pchsource "Swallow/src/swpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/third_party/glm/glm/**.hpp",
		"%{prj.name}/third_party/glm/glm/**.inl"

	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/third_party/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",		
		"ImGui",
		"opengl32.lib"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off" -- in course it is "On"
		systemversion "latest"

		defines
		{
			"SW_PLATFORMS_WINDOWS",
			"SW_BUILD_DLL",
			"_WINDLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			--("{MKDIR} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox"),
			("{MKDIR} \"../bin/" .. outputdir .. "/sandbox\""),

			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox")
		}

	filter "configurations:Debug"
		defines "SW_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SW_RELEASE"
		runtime "Release"
		optimize "On"
			
	filter "configurations:Dist"
		defines "SW_DIST"
		runtime "Release"
		optimize "On"

project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"Swallow/third_party/spdlog/include",
		"Swallow/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Swallow"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"  -- in course it is "On"
		systemversion "latest"

		defines
		{
			"SW_PLATFORMS_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SW_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SW_RELEASE"
		runtime "Release"
		optimize "On"
			
	filter "configurations:Dist"
		defines "SW_DIST"
		runtime "Release"		
		optimize "On"