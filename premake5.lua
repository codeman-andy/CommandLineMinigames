workspace "CommandLineMinigames"
	
	architecture "x64"

	startproject "App"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

	project "App"
		
		location "App"

		kind "ConsoleApp"

		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir    ("obj/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Library/include",
			"Library/src"
		}

		links
		{
			"Library"
		}

		filter "system:windows"
			
			cppdialect "C++20"

			systemversion "latest"
			
			defines
			{
				"HZ_PLATFORM_WINDOWS"
			}

			filter "configurations:Debug"
				defines "CLG_DEBUG"
				symbols "On"
			
			filter "configurations:Release"
				defines "CLG_RELEASE"
				optimize "On"
			
			filter "configurations:Dist"
				defines "CLG_DIST"
				optimize "On"

	project "Library"
		
		location "Library"

		kind "StaticLib"

		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir	  ("obj/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"%{prj.name}/src"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/App")
		}

		filter "system:windows"
			
			cppdialect "C++20"

			systemversion "latest"
			
			defines
			{
				"HZ_PLATFORM_WINDOWS"
			}

			filter "configurations:Debug"
				defines "CLG_DEBUG"
				symbols "On"
			
			filter "configurations:Release"
				defines "CLG_RELEASE"
				optimize "On"
			
			filter "configurations:Dist"
				defines "CLG_DIST"
				optimize "On"