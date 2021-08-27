workspace "imgui_layer"
    architecture "x86_64"
    startproject "sandbox"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "dependencies"
    include "imgui_layer/dependencies/imgui"
group ""

include "imgui_layer"
include "sandbox"
