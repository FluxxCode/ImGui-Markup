#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_IMGUI_LAYER_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_IMGUI_LAYER_H_

/**
 * @file imgui_markup.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Header used for applications using the imgui_layer
 * @copyright Copyright (c) 2021
 */

/*
 * Custom attribute types (data types), which allow the dynamic creation
 * of object attributes through the markup language.
*/
#include "imgui_markup/attribute_types/attribute_type.h"
#include "imgui_markup/attribute_types/bool.h"
#include "imgui_markup/attribute_types/float.h"
#include "imgui_markup/attribute_types/float2.h"
#include "imgui_markup/attribute_types/float3.h"
#include "imgui_markup/attribute_types/float4.h"
#include "imgui_markup/attribute_types/int.h"
#include "imgui_markup/attribute_types/string.h"

/*
 * Every object that can dynamically be created through the markup language.
*/
#include "imgui_markup/objects/global_object.h"
#include "imgui_markup/objects/text.h"
#include "imgui_markup/objects/button.h"
#include "imgui_markup/objects/button_style.h"
#include "imgui_markup/objects/panel.h"
#include "imgui_markup/objects/child_panel.h"
#include "imgui_markup/objects/container.h"
#include "imgui_markup/objects/attribute_types/object_bool.h"
#include "imgui_markup/objects/attribute_types/object_float.h"
#include "imgui_markup/objects/attribute_types/object_float2.h"
#include "imgui_markup/objects/attribute_types/object_float3.h"
#include "imgui_markup/objects/attribute_types/object_float4.h"
#include "imgui_markup/objects/attribute_types/object_int.h"
#include "imgui_markup/objects/attribute_types/object_string.h"

#include "imgui_markup/common_functions.h"

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_IMGUI_LAYER_H_
