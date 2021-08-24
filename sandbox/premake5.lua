--sandbox

project "sandbox"
    kind "ConsoleApp"
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
        "%{wks.location}/imgui_layer/src"
    }

    links
    {
        "imgui_layer"
    }

    filter "system:windows"
        systemversion "latest"
        defines "_IMGUI_LAYER_PLATFORM_WINDOWS"

    filter "configurations:Debug"
        symbols "on"

    filter "configurations:Release"
        optimize "on"
