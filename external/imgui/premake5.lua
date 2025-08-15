project "IMGUI"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	architecture "x64"

	include "../glfw"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	includedirs { 
	"%{prj.location}/imgui/",
	"../glfw/include", 
}

	files
	{
		"imgui/**.h",
        "imgui/**.cpp",
        "imgui/misc/debuggers/imgui.natvis",
        "imgui/misc/debuggers/imgui.natstepfilter",
        "imgui/misc/cpp/imgui_stdlib.*"
	}

	links{
		"GLFW",
	}
    
	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		defines 
		{ 
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"