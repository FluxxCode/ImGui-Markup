#ifndef IMGUI_LAYER_SRC_ILPCH_H_
#define IMGUI_LAYER_SRC_ILPCH_H_

#ifdef _PLATFORM_WINDOWS
    #ifdef _IMGUI_LAYER_DYNAMIC_LINK
        #ifdef _IMGUI_LAYER_BUILD_DLL
            #define IMGUI_LAYER_API  __declspec(dllexport)
        #else
            #define IMGUI_LAYER_API  __declspec(dllimport)
        #endif  // _IMGUI_LAYER_BUILD_DLL
    #else
        #define IMGUI_LAYER_API
    #endif  // _IMGUI_LAYER_DYNAMIC_LINK
#else
    #error Layer only supports windows
#endif  // _PLATFORM_WINDOWS

#include "utility/utility.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <sstream>

#endif  // IMGUI_LAYER_SRC_ILPCH_H_
