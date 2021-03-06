#ifndef IMGUI_MARKUP_SRC_ITEMS_DRAWABLES_CHECKBOX_H_
#define IMGUI_MARKUP_SRC_ITEMS_DRAWABLES_CHECKBOX_H_

#include "items/common/drawable_base.h"

#include "attribute_types/string.h"
#include "attribute_types/bool.h"

namespace igm::internal
{

class Checkbox : public DrawableBase
{
public:
    Checkbox(std::string id, ItemBase* parent);

    Checkbox& operator=(const Checkbox& other);

    String text_;
    Bool is_checked_ = false;

private:
    bool is_hovered_ = false;

    // See item.h for documentation
    void IMPL_Update(Float2 position, Float2 size);
    bool OnProcessStart(std::string& error_message);
    bool OnProcessEnd(std::string& error_message);

    // See item_api.h for documentation
    Bool API_IsItemPressed(MouseButton button) const;
    Bool API_IsItemHovered() const;

    Bool API_IsCheckboxChecked() const;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_DRAWABLES_CHECKBOX_H_
