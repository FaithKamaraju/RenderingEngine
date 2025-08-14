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
IncludeDir["Assimp"] = "external/assimp/include"

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
            "RE_DLL",
            "RE_PLATFORM_WINDOWS",
        }




sourceDir = "%[%{cfg.buildtarget.relpath}]"
destDir = "%[../bin/" .. outputdir .. "/Sandbox/]"
Renderer_libDirs = {}
Renderer_libDirs["Assimp"] = "external/assimp/Binaries/"


project "Renderer"
    location "Renderer"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    libdirs {Renderer_libDirs.Assimp}
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
        IncludeDir.Assimp,
        "Renderer/Renderer/"
    }
    links 
    {
        "GLFW",
        "Glad",
        "GLM",
        "assimp-vc143-mt"
    }
    prebuildcommands
    {
        ("{COPYFILE} %{wks.location}".. Renderer_libDirs.Assimp .. "assimp-vc143-mt.dll ../bin/" .. outputdir .. "/Renderer")
    }
    postbuildcommands
    {
        ("{MKDIR} ../bin/" .. outputdir .. "/Sandbox/"),
        ("{COPYFILE} %{wks.location}".. Renderer_libDirs.Assimp .. "assimp-vc143-mt.dll ../bin/" .. outputdir .. "/Sandbox"),
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
            "ASSIMP_DLL"
        }
    filter {"system:windows","configurations:Release"}
        buildoptions "/MT"

    

    