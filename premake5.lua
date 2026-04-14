workspace "Shadow3D"
architecture "x64"

configurations
{
    "Dev",
    "Release"
}

-- ---------------------------- Shadow3D Project.
project "Shadow3D"
    kind "SharedLib"
    language "C++"
    staticruntime "Off"
    cppdialect "C++20"

    targetdir(path.join("E:/Programming/ScarletProjects/Shadow3D/", "Scratch", "Bin", "%{cfg.buildcfg}", "%{prj.name}"))
    objdir(path.join("E:/Programming/ScarletProjects/Shadow3D/", "Scratch", "Bin-Int", "%{cfg.buildcfg}", "%{prj.name}"))

    files
    {
        "**.h",
        "**.cpp",
    }

    includedirs
    {
        "E:/Programming/ScarletEngine/Deps/Include/",
        "E:/Programming/ScarletEngine/Source/ScarletProject/",
        "E:/Programming/ScarletEngine/Source/ScarletProject/src/",
        "E:/Programming/ScarletEngine/Source/ScarlEntProject/",
        "E:/Programming/ScarletEngine/Source/ScarletMathProject/",
        "E:/Programming/ScarletEngine/Source/ScarletCoreProject/",
        "E:/Programming/ScarletEngine/Source/ScarletReflectProject/",
        "E:/Programming/ScarletEngine/Source/ScarletCoreEcsProject/",
        "E:/Programming/ScarletEngine/Source/ScarletEngineProject/",

        "$(SolutionDir)",
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Dev"
        runtime "Debug"
        defines { "DEV_CONFIGURATION", "GAME_DLL_BUILD" }
        symbols "On"
        links
        {
            "E:/Programming/ScarletEngine/Bin/ScarlEnt.lib",
            "E:/Programming/ScarletEngine/Bin/ScarlEnt.dll",
            "E:/Programming/ScarletEngine/Bin/ScarletMath.lib",
            "E:/Programming/ScarletEngine/Bin/ScarletCore.lib",
            "E:/Programming/ScarletEngine/Bin/ScarletReflect.lib",
            "E:/Programming/ScarletEngine/Bin/ScarletCoreEcs.lib",
            "E:/Programming/ScarletEngine/Bin/ScarletEngine.lib",
            "E:/Programming/ScarletEngine/Bin/ScarletEngine.dll"
        }

    filter "configurations:Release"
        runtime "Release"
        defines "GAME_DLL_BUILD"
        optimize "On"
        links
        {
            "E:/Programming/ScarletEngine/Build/Bin/ScarlEnt.lib",
            "E:/Programming/ScarletEngine/Build/Bin/ScarlEnt.dll",
            "E:/Programming/ScarletEngine/Build/Bin/ScarletMath.lib",
            "E:/Programming/ScarletEngine/Build/Bin/ScarletCore.lib",
            "E:/Programming/ScarletEngine/Build/Bin/ScarletReflect.lib",
            "E:/Programming/ScarletEngine/Build/Bin/ScarletCoreEcs.lib",
            "E:/Programming/ScarletEngine/Build/Bin/ScarletEngine.lib",
            "E:/Programming/ScarletEngine/Build/Bin/ScarletEngine.dll"
        }