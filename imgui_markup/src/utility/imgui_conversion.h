#ifndef IMGUI_MARKUP_SRC_UTILITY_H_
#define IMGUI_MARKUP_SRC_UTILITY_H_

#include "input.h"

#include "imgui.h"

// Conversion functions between custom and imgui types
namespace igm::internal
{

ImGuiMouseButton MouseButtonToImGui(MouseButton mouse_button);

}  // namespace igm::internal


#endif  // IMGUI_MARKUP_SRC_UTILITY_H_
