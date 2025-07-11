workspace "ImDemo"
    location (".")
    configurations { "Debug", "Release" }
    platforms { "Win64" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        optimize "Off"
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "Full"
    filter "*"

    targetdir ("./Build/Bin/%{prj.name}/%{cfg.buildcfg}/")
    objdir ("./Build/Obj/%{prj.name}/%{cfg.buildcfg}/")
    startproject "ImDemo"

    cppdialect "C++20"

project "ImDemo"
    kind "WindowedApp"
    language "C++"
    location ("./Build/Projects/".. _ACTION)

    includedirs  {"./Source/**"}

    -- links
    libdirs { "./Source/Extensions/glfw/lib-vc2010-64/", "./Source/Extensions/FreeType2/lib/", "./Source/Extensions/vulkan/lib/" }
    links { "glfw3.lib", "freetype.lib", "vulkan-1.lib" }

    -- files
    files { "./Source/GUI/**.h", "./Source/GUI/**.c", "./Source/GUI/**.cc", "./Source/GUI/**.cpp" }

    filter "configurations:Debug"
        libdirs { "./Build/Bin/%{prj.name}/Debug/" }
    filter "configurations:Release"
        libdirs { "./Build/Bin/%{prj.name}/Release/" }
    filter "*"
