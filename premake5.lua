workspace "ray_prac_work"
    architecture "x64"
    startproject "ray_prac_con"

    configurations {
        "Debug",
        "Release"
    }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
LibDirs = {}

IncludeDirs["raylib"] = "%{wks.location}/ray_prac_con/vendor/raylib/include"
IncludeDirs["imguiDir"] = "%{wks.location}/ray_prac_con/vendor/imgui"
IncludeDirs["rlImgui"] = "ray_prac_con/vendor/rlImGui"
LibDirs["raylib"] = "ray_prac_con/vendor/raylib/lib"

include "ray_prac_con/vendor/imgui"
include "ray_prac_con/vendor/rlImGui"

project "ray_prac_con"
    location "ray_prac_con"
    kind "ConsoleApp"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/src/Chess",
        "%{IncludeDirs.raylib}",
        "%{IncludeDirs.imguiDir}",
        "%{IncludeDirs.rlImgui}",
    }

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    libdirs {
        "%{LibDirs.raylib}"
    }

    links {
        "raylib",
        "ImGui",
        "rlImGui",
        "winmm"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"


