include "dependencies.lua"

workspace "imgui_layer"
    architecture "x86_64"
    startproject "sandbox"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "dependencies"
    include "imgui_layer/dependencies/imgui"
    include "sandbox/dependencies/glfw"
group ""

include "imgui_layer"
include "sandbox"
