#ifndef IMGUI_MARKUP_SRC_OBJECTS_GLOBAL_OBJECT_H_
#define IMGUI_MARKUP_SRC_OBJECTS_GLOBAL_OBJECT_H_

#include "objects/common/object_base.h"
#include "attribute_types/string.h"

namespace imgui_markup::internal
{

struct FileContext
{
    /**
     * Stores a reference to every child object with an ID.
     * Those are the main IDs that are used to identify objects.
     * The IDs are loaded and set by the interpreter.
     *
     * The structure of the buffer is:
     * root_id.child_id.child_id.child_id.object_id
     * Where:
     * root_id   = highest parent object with an ID
     * child_id  = objects with an ID between the root object and the
     *             referenced object
     * object_id = ID of the referenced object
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
    std::map<std::string, ObjectBase&> object_references_;

    /**
     * Stores the main object tree.
     */
    std::vector<std::shared_ptr<ObjectBase>> object_tree_;
};

}  // namespace imgui_markup::internal
#endif  // IMGUI_MARKUP_SRC_OBJECTS_GLOBAL_OBJECT_H_
