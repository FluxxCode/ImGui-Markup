#ifndef IMGUI_LAYER_SRC_OBJECTS_OBJECT_H_
#define IMGUI_LAYER_SRC_OBJECTS_OBJECT_H_

#include "imgui_layer/attribute_types/attribute_type.h"
#include "imgui_layer/attribute_types/float2.h"
#include "imgui_layer/parser/parser_result.h"

#include <string>
#include <map>
#include <vector>
#include <memory>

namespace gui
{

class Interpreter;  // Used as a friend class

class Object
{
public:
    Float2 position_;
    Float2 size_;

    /**
     * @param[in] type   - Type of the object
     * @param[in] id     - ID of the object
     * @param[in] parent - Pointer to the parent object, nullptr
     *                     if the object has no parent object.
    */
    Object(std::string type, std::string id, Object* parent);

    /**
     * Main update function that should be called every frame.
     */
    virtual void Update() { };

    /**
     * Get a pointer to an attribute from this object by its name.
     *
     * @param[in] name - The name of the attribtue.
     *
     * @return a pointer to the attribute. nullptr, if the attribute with the
     *         given name does not exists.
    */
    Attribute* GetAttribute(const std::string name) const;

    inline std::string GetID()     const { return this->id_; }
    inline std::string GetType()   const { return this->type_; }
    inline Object*     GetParent() const { return this->parent_; }

protected:
    std::string type_;
    std::string id_;
    Object* parent_;
    std::vector<std::shared_ptr<Object>> child_objects_ = { };

    // Functions
    /**
     * Call the update function of every child object.
    */
    void UpdateChilds();

    /**
     * Add an attribute to the attribute list.
     *
     * @param[in] name      - The name of the attribute, that can be used to
     *                        access the attribute from data that is parsed.
     * @param[in] attribute - An pointer to the attribute.
    */
    void AddAttribute(const std::string name, Attribute* attribute);

    /**
     * Remove an attribute from the attribute list.
     * Used to remove the default attributes that are added
     * by this class.
     *
     * @param[in] name - The name of the attribute that will be removed.
    */
    void RemoveAttribute(const std::string name);

private:
    friend class Interpreter;

    std::map<std::string, Attribute*> attribute_list_ = { };

    /**
     * Adds an child object to the child_objects_ variable.
     */
    void AddChild(std::shared_ptr<Object> child);

    /**
     * Verifys that the object is valid.
     * The function should be called by the interpreter and is used to
     * e.g. make sure that the object has the correct parent.
     * Some objects are only allowed to have a parent object of a specific
     * type.
     *
     * @param[in] error_message - String that will be set to the error
     *                            if there is one.
     * @return true - If the object is valid.
     * @return false - If the object is currently not valid.
     *                 The error message will be set to the reason why the
     *                 object is not valid.
     */
    virtual bool Verify(std::string& error_message) const { return true; }

    /**
     * Function that is called by the interpreter before the interpreter
     * starts the process of the objects child nodes.
     * This can be used to e.g. add attributes to its parent object.
     *
     * @param[in] error_message - String that will be set to the error message
     *                            if there is one.
     */
    virtual bool OnProcessStart(std::string& error_message) { return true; }

    /**
     * Function that is called by the interpreter after the interpreter
     * processed the objects child nodes.
     * This can be used to e.g. add attributes to its child objects or
     * to make sure that specific attributes are set.
     *
     * @param[in] error_message - String that will be set to the error message
     *                            if there is one.
     */
    virtual bool OnProcessEnd(std::string& error_message) { return true; }
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_OBJECT_H_
