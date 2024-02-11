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

IncludeDirs["raylib"] = "ray_prac_con/vendor/raylib-5.0/include"
LibDirs["raylib"] = "ray_prac_con/vendor/raylib-5.0/lib"


project "ray_prac_con"
    location "ray_prac_con"
    kind "ConsoleApp"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{prj.name}/src",
        "%{IncludeDirs.raylib}",
    }
    libdirs {
        "%{LibDirs.raylib}",
    }

    links {
        "OpenGL32",
        "GDI32",
        "WinMM",
        "raylib",

    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"


