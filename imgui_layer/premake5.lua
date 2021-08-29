project "imgui_layer"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

    pchheader "ilpch.h"
    pchsource "src/ilpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "%{include_dir.imgui}",
    }

    links
    {
        "imgui"
    }

    filter "system:windows"
        systemversion "latest"
        defines "_PLATFORM_WINDOWS"

    filter "configurations:Debug"
        symbols "on"

    filter "configurations:Release"
        optimize "on"
