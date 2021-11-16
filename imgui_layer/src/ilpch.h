#ifndef IMGUI_LAYER_SRC_ILPCH_H_
#define IMGUI_LAYER_SRC_ILPCH_H_

#if defined(_MSC_VER)
    //  Microsoft
#elif defined(__GNUC__)
    //  GCC
#else
    #error Layer only supports windows and linux
#endif  // _PLATFORM_WINDOWS || _PLATFORM_LINUX

#include "utility/utility.h"

#include "imgui.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <fstream>

#endif  // IMGUI_LAYER_SRC_ILPCH_H_
