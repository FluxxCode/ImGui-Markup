#ifndef IMGUI_MARKUP_SRC_ITEMS_GLOBAL_ITEM_H_
#define IMGUI_MARKUP_SRC_ITEMS_GLOBAL_ITEM_H_

#include "items/item_base.h"
#include "attribute_types/string.h"

namespace imgui_markup::internal
{

struct FileContext
{
    /**
     * Stores a reference to every child item with an ID.
     * Those are the main IDs that are used to identify items.
     * The IDs are loaded and set by the interpreter.
     *
     * The structure of the buffer is:
     * root_id.child_id.child_id.child_id.item_id
     * Where:
     * root_id   = highest parent item with an ID
     * child_id  = items with an ID between the root item and the
     *             referenced item
     * item_id = ID of the referenced item
     *
     * Example:
     * Panel : panel_0
     * {
     *      ChildPanel : cild_panel
     *      {
     *          ChildPanel
     *          {
     *              Button : button_0 { }
     *          }
     *      }
     * }
     * Will be stored as:
     * "panel_0.child_panel.button_0" -> Button
     */
    std::map<std::string, ItemBase&> item_references_;

    /**
     * Stores the main item tree.
     */
    std::vector<std::shared_ptr<ItemBase>> item_tree_;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_GLOBAL_ITEM_H_
