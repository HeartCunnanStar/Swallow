project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"
	-- warnings "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/Glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
    {
        "include"
    }

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	-- filter { "system:windows", "configurations:Debug-AS" }	
	-- 	runtime "Debug"
	-- 	symbols "on"
	-- 	sanitize { "Address" }
	-- 	flags { "NoRuntimeChecks", "NoIncrementalLink" }

    -- filter "configurations:Dist"
	-- 	runtime "Release"
	-- 	optimize "speed"
    --     symbols "off"
