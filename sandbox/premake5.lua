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
        "%{wks.location}/imgui_layer/src",
        "%{include_dir.imgui}",
        "%{include_dir.glfw}",
    }

    links
    {
        "imgui_layer",
        "imgui",
        "glfw",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"
        defines "_PLATFORM_WINDOWS"

    filter "configurations:Debug"
        symbols "on"

    filter "configurations:Release"
        optimize "on"
