#ifndef IMGUI_MARKUP_SRC_ITEMS_CONTAINER_H_
#define IMGUI_MARKUP_SRC_ITEMS_CONTAINER_H_

#include "items/common/item_base.h"

namespace imgui_markup::internal
{

class Container : public ItemBase
{
public:
    Container(std::string id, ItemBase* parent);
    Container(const Container&) = delete;

private:
    // See item.h for documentation
    void IMPL_Update(Float2 position, Float2 size);
    bool OnProcessStart(std::string& error_message);
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_BUTTON_H_
