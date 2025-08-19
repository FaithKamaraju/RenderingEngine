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
IncludeDir["GLFW"] = "external/glfw/include" 
IncludeDir["Glad"] = "external/glad/include"
IncludeDir["GLM"]  = "external/glm/"
IncludeDir["Assimp"] = "external/assimp/include"
IncludeDir["ImGui"] = "external/imgui/"

include "external/glfw"
include "external/glad"
include "external/glm"
include "external/imgui"





project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/")
    objdir ("bin-int/" .. outputdir .. "/")
    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        IncludeDir.GLM,
        "%{wks.location}/FEEngine"
    }

    links
    {
        "FEEngine",
        "GLM"
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
        }












FEEngine_libDirs = {}
FEEngine_libDirs["Assimp"] = "external/assimp/Binaries/"

project "FEEngine"
    location "FEEngine"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/")
    objdir ("bin-int/" .. outputdir .. "/")
    libdirs {FEEngine_libDirs.Assimp}
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
        IncludeDir.ImGui,
        IncludeDir.Assimp,
        "%{prj.location}"
    }
    links 
    {
        "GLFW",
        "Glad",
        "GLM",
        "IMGUI",
        "assimp-vc143-mt",
    }
    prebuildcommands
    {
        ("{COPYFILE} %{wks.location}".. FEEngine_libDirs.Assimp .. "assimp-vc143-mt.dll ../bin/" .. outputdir .."")
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







FEEditor_libDirs = {}
FEEditor_libDirs["Assimp"] = "external/assimp/Binaries/"

project "FEEditor"
    location "FEEditor"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/")
    objdir ("bin-int/" .. outputdir .. "/")
    libdirs {FEEditor_libDirs.Assimp}
    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        IncludeDir.GLM,
        IncludeDir.ImGui,
        "%{wks.location}/FEEngine/"
    }
    links 
    {
        "GLM",
        "IMGUI",
        "FEEngine",
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
        }
    filter {"system:windows","configurations:Release"}
        buildoptions "/MT"









-- Renderer_libDirs = {}
-- Renderer_libDirs["Assimp"] = "external/assimp/Binaries/"

-- project "FERenderer"
--     location "FERenderer"
--     kind "SharedLib"
--     language "C++"
--     targetdir ("bin/" .. outputdir .. "/")
--     objdir ("bin-int/" .. outputdir .. "/")
--     libdirs {Renderer_libDirs.Assimp}
--     files
--     {
--         "%{prj.name}/**.h",
--         "%{prj.name}/**.cpp"
--     }

--     includedirs
--     {
--         IncludeDir.GLFW,
--         IncludeDir.Glad,
--         IncludeDir.GLM,
--         IncludeDir.Assimp,
--         IncludeDir.ImGui,
--         "%{prj.location}",
--         "%{wks.location}/FEEngine/"
--     }
--     links 
--     {
--         "GLFW",
--         "Glad",
--         "GLM",
--         "IMGUI",
--         "assimp-vc143-mt",

--         "FEEngine",
--     }
--     prebuildcommands
--     {
--         ("{COPYFILE} %{wks.location}".. Renderer_libDirs.Assimp .. "assimp-vc143-mt.dll ../bin/" .. outputdir .."")
--     }

--     filter "configurations:Debug"
--       defines { "FE_DEBUG" }
--       symbols "On"

--     filter "configurations:Release"
--       defines { "FE_RELEASE" }
--       optimize "On"

--     filter "configurations:Dist"
--       defines { "FE_DIST" }
--       optimize "On"

--     filter "system:windows"
--         cppdialect "C++20"
--         staticruntime "On"
--         systemversion "latest"
--         defines
--         {
--             "FE_PLATFORM_WINDOWS",
--             "FE_DLL",
--             "FER_BUILD_DLL",
--             "ASSIMP_DLL"
--         }
--     filter {"system:windows","configurations:Release"}
--         buildoptions "/MT"



    

    