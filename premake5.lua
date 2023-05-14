workspace "PaperEditor"
	architecture "x64"
	startproject "PaperEditor"
	staticruntime "off"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "lib/core/GLFW/include"
IncludeDir["GLAD"] = "lib/core/GLAD/include"
IncludeDir["IMGUI"] = "lib/core/IMGUI_DOCKING"
IncludeDir["IMPLOT"] = "lib/core/IMPLOT"
IncludeDir["SPDLOG"] = "lib/SPDLOG/include"
IncludeDir["MINIAUDIO"] = "lib/MINIAUDIO"
IncludeDir["msdfgen"] = "lib/core/msdf-atlas-gen/msdfgen"
IncludeDir["msdf_atlas_gen"] = "lib/core/msdf-atlas-gen/msdf-atlas-gen"

group "dependencies"
include "lib/core/GLFW"
include "lib/core/GLAD"
include "lib/core/IMGUI_DOCKING"
include "lib/core/IMPLOT"
include "lib/core/msdf-atlas-gen"
group ""

project "engine"
	location "engine"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Engine.h"
	pchsource "engine/src/Engine.cpp"

	files
	{
		"%{prj.name}/lib/**.h",
		"%{prj.name}/lib/**.gch",
		"%{prj.name}/lib/**.hpp",
		"%{prj.name}/lib/**.cpp",
		"%{prj.name}/lib/**.c",
		"%{prj.name}/lib/**.lib",
		"%{prj.name}/lib/**.dll",
		"%{prj.name}/lib/**.a",

		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"lib",
		"%{prj.name}/lib",
		"%{prj.name}/src",
		"%{prj.name}/src/core",
		"%{prj.name}/src/platform",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.IMPLOT}",
		"%{IncludeDir.SPDLOG}",
		"%{IncludeDir.MINIAUDIO}",		
		"%{IncludeDir.msdfgen}",
		"%{IncludeDir.msdf_atlas_gen}"
	}

	links 
	{
		"GLFW",
		"GLAD",
		"IMGUI",
		"IMPLOT",
		"opengl32.lib",
		"msdf-atlas-gen"
	}

	disablewarnings 
	{
		"4005",
		"4244",
		"4312",
		"4267",
		"4251"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"CORE_PLATFORM_WINDOWS",
			"CORE_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"CORE_ENABLE_ASSERTS"
		}

	filter "configurations:Debug"
		defines "BUILD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BUILD_RELEASE"
		optimize "On"


project "PaperEditor"
	location "PaperEditor"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Editor.h"
	pchsource "PaperEditor/src/Editor.cpp"

	files
	{
		"%{prj.name}/lib/**.h",
		"%{prj.name}/lib/**.gch",
		"%{prj.name}/lib/**.hpp",
		"%{prj.name}/lib/**.cpp",
		"%{prj.name}/lib/**.c",
		"%{prj.name}/lib/**.lib",
		"%{prj.name}/lib/**.dll",
		"%{prj.name}/lib/**.a",

		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"lib",
		"%{prj.name}/lib",
		"%{prj.name}/src",
		"engine/src",
		"engine/src/core",
		"engine/lib",
		"%{IncludeDir.SPDLOG}",
		"%{IncludeDir.MINIAUDIO}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.IMPLOT}",
		"%{IncludeDir.msdfgen}",
		"%{IncludeDir.msdf_atlas_gen}"
	}

	links
	{
		"engine"
	}

	disablewarnings
	{
		"4251",
		"4267",
		"4305",
		"4244"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"CORE_PLATFORM_WINDOWS",
			"CORE_ENABLE_ASSERTS"
		}

	filter "configurations:Debug"
		defines "BUILD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BUILD_RELEASE"
		optimize "On"
