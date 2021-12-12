#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_IMGUI_LAYER_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_IMGUI_LAYER_H_

/**
 * @file imgui_layer.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Header used for applications using the imgui_layer
 * @copyright Copyright (c) 2021
 */

/*
 * Custom attribute types (data types), which allow the dynamic creation
 * of object attributes through the markup language.
*/
#include "imgui_layer/attribute_types/attribute_type.h"
#include "imgui_layer/attribute_types/bool.h"
#include "imgui_layer/attribute_types/float.h"
#include "imgui_layer/attribute_types/float2.h"
#include "imgui_layer/attribute_types/float3.h"
#include "imgui_layer/attribute_types/float4.h"
#include "imgui_layer/attribute_types/int.h"
#include "imgui_layer/attribute_types/string.h"

/*
 * Every object that can dynamically be created through the markup language.
*/
#include "imgui_layer/objects/global_object.h"
#include "imgui_layer/objects/text.h"
#include "imgui_layer/objects/button.h"
#include "imgui_layer/objects/panel.h"
#include "imgui_layer/objects/child_panel.h"

#include "imgui_layer/parser/file_manager.h"

#include "imgui_layer/common_functions.h"

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_IMGUI_LAYER_H_
