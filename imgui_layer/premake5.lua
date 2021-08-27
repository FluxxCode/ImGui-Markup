project "imgui_layer"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src"
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
