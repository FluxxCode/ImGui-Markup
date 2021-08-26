#ifndef IMGUI_LAYER_SRC_CORE_H_
#define IMGUI_LAYER_SRC_CORE_H_

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

#endif  // IMGUI_LAYER_SRC_CORE_H_
