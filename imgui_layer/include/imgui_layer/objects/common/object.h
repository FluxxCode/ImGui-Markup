#ifndef IMGUI_LAYER_SRC_OBJECTS_OBJECT_H_
#define IMGUI_LAYER_SRC_OBJECTS_OBJECT_H_

#include "imgui_layer/attribute_types/attribute_type.h"
#include "imgui_layer/attribute_types/float2.h"
#include "imgui_layer/parser/parser_error.h"

#include <string>
#include <map>
#include <vector>
#include <memory>

namespace gui
{

class Object
{
public:
    // Variables
    Float2 position_;
    Float2 size_;

    // Constructors/Destructor
    /**
     * @param[in] name   - Name/type of the object
     * @param[in] id     - ID of the object
     * @param[in] parent - Pointer to the parent object, nullptr
     *                     if the object has no parent object.
    */
    Object(std::string name, std::string id, Object* parent);

    // Functions
    virtual void Update() = 0;

    /**
     * Load the value of an attribute from this object by its name.
     *
     * @param[in] name - The name of the attribute where the value gets loaded.
     * @param[in] value - The value that will be loaded into the attribute.
     *
     * @return true if the value was loaded successfully into the attribute.
     *         False, if the attribtue with the name does not exists or there
     *         was an error when loading the value into the attribute.
    */
    bool SetAttributeValue(const std::string name, const std::string value);

    /**
     * Get a pointer to an attribute from this object by its name.
     *
     * @param[in] name - The name of the attribtue.
     *
     * @return a pointer to the attribute. nullptr, if the attribute with the
     *         given name does not exists.
    */
    AttributeType* GetAttribute(const std::string name) const;

    /**
     * Check if this object has an attribute with the given name.
     *
     * @param[in] name - The name of the attribtue that will be chacked.
     *
     * @return true if an attribute with the name exists,
     *         false if there is no attribute with the given name.
    */
    bool HasAttribute(const std::string name) const;

    /**
     * Check if this object has a parent object.
     *
     * @return true if this object has a parent object,
     *         false if this object has no parent object.
    */
    bool HasParent();

    /**
     * Get a shared_ptr to an child object from this object by its name.
     *
     * @param[in] id        - The id of the child object.
     * @param[in] recursive - Specifies whether the child objects are also
     *                        searched for an child object by the given ID.
     *
     * return shared_ptr to the child object with the given ID.
     *        A nullptr will be returned if there is no child object with the
     *        given ID.
    */
    std::shared_ptr<Object> GetChild(
        const std::string id,
        bool recursive = true) const;

    /**
     * Add an object as a child object to this object.
     * The object must already exist.
     *
     * @oaram[in] child - A pointer to the object that will be added
     *                    as a child oject.
    */
    void AddChild(std::shared_ptr<Object> child);

    /**
     * Get the name of the object.
    */
    std::string GetName() const;

    /**
     * Get the ID of this object.
     *
     * @return the ID of this object. An empty string will be returned if
     *         this object has no ID.
    */
    std::string GetID() const;

    ParserError GetLastError() const;

protected:
    // Variables
    std::string name_;
    std::string id_;
    Object* parent_;

    std::vector<std::shared_ptr<Object>> child_objects_ = { };

    mutable ParserError last_error_;

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
    void AddAttribute(const std::string name, AttributeType* attribute);

    /**
     * Remove an attribute from the attribute list.
     * Used to remove the default attributes that are added
     * by this class.
     *
     * @param[in] name - The name of the attribute that will be removed.
    */
    void RemoveAttribute(const std::string name);

private:
    // Variables
    std::map<std::string, AttributeType*> attribute_list_ = { };

};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_OBJECT_H_
