#include "impch.h"
#include "utility/imgui_conversion.h"

#include <assert.h>

namespace imgui_markup::internal
{

ImGuiMouseButton MouseButtonToImGui(MouseButton mouse_button)
{
    switch (mouse_button)
    {
    case MouseButton::kLeft: return ImGuiMouseButton_Left;
    case MouseButton::kRight: return ImGuiMouseButton_Right;
    case MouseButton::kMiddle: return ImGuiMouseButton_Middle;
    default: assert("Undefined MouseButton");
    }

    // Will never be reached; just to prevent warnings
    return ImGuiMouseButton_Left;
}

}  // namespace imgui_markup::internal
