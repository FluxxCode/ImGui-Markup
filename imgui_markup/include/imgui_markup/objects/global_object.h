#ifndef IMGUI_LAYER_SRC_OBJECTS_GLOBAL_OBJECT_H_
#define IMGUI_LAYER_SRC_OBJECTS_GLOBAL_OBJECT_H_

#include "imgui_markup/objects/common/object.h"

#include "imgui_markup/attribute_types/string.h"

namespace imgui_markup
{

namespace internal::parser
{
class Interpreter;  // Used as a friend class
}

class GlobalObject : public Object
{
public:
    String id_;
    String version_;
    String description_;
    String author_;
    String date_;

    GlobalObject();

    GlobalObject& operator=(const GlobalObject& other);

    void Update();

    /**
     * Resets every attribute from this object.
    */
    void Reset();

    /**
     * Checks if one or more of the child objects are hovered.
     */
    bool IsHovered() const noexcept;

    /**
     * Checks if the object with the given ID is hovered.
     * The function always returns false if the object with the given
     * ID does not exists.
     */
    bool IsHovered(std::string object_id) const noexcept;

    /**
     * Checks if one or more of the child objects are pressed.
     *
     * @param button = Specifies the button that will be
     *                 checked if it is presed.
     */
    bool IsPressed(
        ImGuiMouseButton button = ImGuiMouseButton_Left) const noexcept;

    /**
     * Checks if the object with the given ID is pressed.
     * The function always returns false if the object with the given
     * ID does not exists.
     *
     * @param button = Specifies the button that will be
     *                 checked if it is presed.
     */
    bool IsPressed(std::string object_id,
        ImGuiMouseButton button = ImGuiMouseButton_Left) const noexcept;

private:
    friend class internal::parser::Interpreter;

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
    Object* GetObjectReference(std::string object_id) const noexcept;

    /**
     * Checks if the given object is hovered.
     */
    bool IsHovered(const Object& object) const noexcept;
};

}  // namespace imgui_markup

#endif  // IMGUI_LAYER_SRC_OBJECTS_GLOBAL_OBJECT_H_
