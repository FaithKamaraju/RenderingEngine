workspace "RenderingEngine"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "external/glfw/include" 
IncludeDir["Glad"] = "external/glad/include"
IncludeDir["GLM"]  = "external/glm/"

include "external/glfw"
include "external/glad"
include "external/glm"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        IncludeDir.GLM,
        "Renderer/"
    }

    links
    {
        "Renderer",
        "GLM"
    }

    filter "configurations:Debug"
      defines { "RE_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "RE_RELEASE" }
      optimize "On"
    
   filter "configurations:Dist"
      defines { "RE_DIST" }
      optimize "On"

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "RE_PLATFORM_WINDOWS",
        }




sourceDir = "%[%{cfg.buildtarget.relpath}]"
destDir = "%[../bin/" .. outputdir .. "/Sandbox/]"

project "Renderer"
    location "Renderer"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        IncludeDir.GLFW,
        IncludeDir.Glad,
        IncludeDir.GLM,
        "Renderer/Renderer/"
    }
    links 
    {
        "GLFW",
        "Glad",
        "GLM"
    }
    postbuildcommands
    {
        ("{MKDIR} ../bin/" .. outputdir .. "/Sandbox/"),
        ("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
    }

    filter "configurations:Debug"
      defines { "RE_DEBUG" }
      symbols "On"

    filter "configurations:Release"
      defines { "RE_RELEASE" }
      optimize "On"

    filter "configurations:Dist"
      defines { "RE_DIST" }
      optimize "On"

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "RE_PLATFORM_WINDOWS",
            "RE_BUILD_DLL",
        }
    filter {"system:windows","configurations:Release"}
        buildoptions "/MT"

    

    