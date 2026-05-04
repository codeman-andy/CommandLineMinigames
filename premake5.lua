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
			"Battleship/src",
			"Library/include",
			"TicTacToe/src"
		}

		links
		{
			"Battleship",
			"TicTacToe"
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

	project "Battleship"

		location "Battleship"

		kind "StaticLib"

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
			"Library/include"
		}

		links
		{
			"Library"
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

	project "Library"
		
		location "Library"

		kind "StaticLib"

		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir	  ("obj/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/include/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"%{prj.name}/include"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/App"),
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Battleship"),
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/TicTacToe")
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

	project "TicTacToe"
		
		location "TicTacToe"

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
			"Library/include"
		}

		links
		{
			"Library"
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