project "IMGUI"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	architecture "x64"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	includedirs { 
	"./imgui/",
}

	files
	{
		"./imgui/**.h",
        "./imgui/**.cpp",
        "./imgui/misc/debuggers/imgui.natvis",
        "./imgui/misc/debuggers/imgui.natstepfilter",
        "./imgui/misc/cpp/imgui_stdlib.*"
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