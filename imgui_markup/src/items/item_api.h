#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_API_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_API_H_

#include "attribute_types/bool.h"

#include "input.h"

namespace igm::internal
{

struct ItemAPI
{

virtual Bool API_IsPressed(MouseButton button) const { return false; }
virtual Bool API_IsHovered() const { return false; }
virtual Bool API_IsChecked() const { return false; }

};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_API_H_
