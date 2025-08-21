workspace "FEEngine"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
startproject "FEEditor"


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Glad"] = "external/glad/include"
IncludeDir["GLM"]  = "external/glm/"
IncludeDir["Assimp"] = "external/assimp/include"
IncludeDir["ImGui"] = "external/imgui/"
IncludeDir["sdl3"] = "external/sdl3/include"

include "external/glad"
include "external/glm"
include "external/imgui"

FEEngineCore_libDirs = {}
FEEngineCore_libDirs["Assimp"] = "external/assimp/Binaries/"
FEEngineCore_libDirs["sdl3"] = "external/sdl3/Binaries/"

EnginePaths = {}
EnginePaths["FEEngineCore"] = "%{wks.location}/bin/" .. outputdir .. "/FEEngineCore/FEEngineCore.dll"



project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/")
    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        IncludeDir.GLM,
        "%{wks.location}/FEEngineCore"
    }

    links
    {
        "FEEngineCore",
        "GLM"
    }
    prebuildcommands
    {
        ("{COPYFILE} %{wks.location}".. FEEngineCore_libDirs.sdl3 .. "SDL3.dll ../bin/" .. outputdir .."/%{prj.name}"),
        ("{COPYFILE} %{wks.location}".. FEEngineCore_libDirs.Assimp .. "assimp-vc143-mt.dll ../bin/" .. outputdir .."/%{prj.name}"),
        ("{COPYFILE} " .. EnginePaths.FEEngineCore .. " ../bin/" .. outputdir .. "/%{prj.name}")
    }

    filter "configurations:Debug"
      defines { "FE_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "FE_RELEASE" }
      optimize "On"
    
   filter "configurations:Dist"
      defines { "FE_DIST" }
      optimize "On"

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "FE_DLL",
            "FE_PLATFORM_WINDOWS",
            "FE_GAME",
        }














project "FEEngineCore"
    location "FEEngineCore"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/")
    libdirs {FEEngineCore_libDirs.Assimp, FEEngineCore_libDirs.sdl3}
    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        IncludeDir.Glad,
        IncludeDir.GLM,
        IncludeDir.ImGui,
        IncludeDir.Assimp,
        IncludeDir.sdl3,
        "%{prj.location}"
    }
    links 
    {
        "Glad",
        "GLM",
        "IMGUI",
        "assimp-vc143-mt",
        "SDL3",
    }
    prebuildcommands
    {
        ("{COPYFILE} %{wks.location}".. FEEngineCore_libDirs.sdl3 .. "SDL3.dll ../bin/" .. outputdir .."/%{prj.name}"),
        ("{COPYFILE} %{wks.location}".. FEEngineCore_libDirs.Assimp .. "assimp-vc143-mt.dll ../bin/" .. outputdir .."/FEEngineCore"),
    }
    

    filter "configurations:Debug"
      defines { "FE_DEBUG" }
      symbols "On"

    filter "configurations:Release"
      defines { "FE_RELEASE" }
      optimize "On"

    filter "configurations:Dist"
      defines { "FE_DIST" }
      optimize "On"

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "FE_PLATFORM_WINDOWS",
            "FE_BUILD_DLL",
        }
    filter {"system:windows","configurations:Release"}
        buildoptions "/MT"








project "FEEditor"
    location "FEEditor"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/")
    libdirs {FEEngineCore_libDirs.Assimp}
    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        IncludeDir.GLM,
        IncludeDir.ImGui,
        "%{wks.location}/FEEngineCore/"
    }
    links 
    {
        "GLM",
        "IMGUI",
        "FEEngineCore",
    }
    prebuildcommands
    {
        ("{COPYFILE} %{wks.location}".. FEEngineCore_libDirs.sdl3 .. "SDL3.dll ../bin/" .. outputdir .."/%{prj.name}"),
        ("{COPYFILE} %{wks.location}".. FEEngineCore_libDirs.Assimp .. "assimp-vc143-mt.dll ../bin/" .. outputdir .."/%{prj.name}"),
        ("{COPYFILE} " .. EnginePaths.FEEngineCore .. " ../bin/" .. outputdir .. "/%{prj.name}")
    }
    

    filter "configurations:Debug"
      defines { "FE_DEBUG" }
      symbols "On"

    filter "configurations:Release"
      defines { "FE_RELEASE" }
      optimize "On"

    filter "configurations:Dist"
      defines { "FE_DIST" }
      optimize "On"

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "FE_PLATFORM_WINDOWS",
            "FE_DLL",
            "FE_EDITOR",
        }
    filter {"system:windows","configurations:Release"}
        buildoptions "/MT"    