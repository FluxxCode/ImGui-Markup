#ifndef IMGUI_LAYER_SRC_OBJECTS_GLOBAL_OBJECT_H_
#define IMGUI_LAYER_SRC_OBJECTS_GLOBAL_OBJECT_H_

#include "imgui_layer/objects/common/object.h"

#include "imgui_layer/attribute_types/string.h"

namespace gui
{

class Interpreter;

class GlobalObject : public Object
{
public:
    // Constructors/Destructors
    GlobalObject();

    // Functions
    void Update();

    /**
     * Resets every attribute from this object.
    */
    void Reset();

    // Variables
    String id_;
    String version_;
    String description_;
    String author_;
    String date_;

private:
    friend class Interpreter;

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
    std::map<std::string, Object&> object_references_;

    /**
     * Gets an object by its object ID from the object references.
     *
     * @param object_id - ID of the object that will be returned
     * @return pointer to object, nullptr if the object does not exists.
     */
    Object* GetObjectReference(std::string object_id);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_GLOBAL_OBJECT_H_
