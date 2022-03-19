#ifndef IMGUI_MARKUP_SRC_ITEMS_CONTAINER_CHILD_PANEL_H_
#define IMGUI_MARKUP_SRC_ITEMS_CONTAINER_CHILD_PANEL_H_

#include "items/common/container_base.h"

#include "attribute_types/bool.h"
#include "attribute_types/string.h"
#include "attribute_types/float2.h"

namespace imgui_markup::internal
{

class ChildPanel : public ContainerBase
{
public:
    // Constructor/Destructor
    ChildPanel(std::string id, ItemBase* parent);
    ChildPanel(const ChildPanel&) = delete;

    Float2 padding_;

    String title_;
    Bool border_;

private:
    bool is_hovered_ = false;

    void InitPositionAndSize(Float2 position, Float2 size);

    Float2 CalculateChildPosition() const;
    Float2 CalculateChildSize(Float2 size) const;

    // See item.h for documentation
    void IMPL_Update(Float2 position, Float2 size);
    bool OnProcessStart(std::string& error_message);
    bool OnProcessEnd(std::string& error_message);

    // See item_api.h for documentation
    Bool API_IsPressed(MouseButton button) const;
    Bool API_IsHovered() const;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_CONTAINER_CHILD_PANEL_H_
