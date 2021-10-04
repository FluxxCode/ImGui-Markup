#ifndef IMGUI_LAYER_SRC_OBJECTS_OBJECT_H_
#define IMGUI_LAYER_SRC_OBJECTS_OBJECT_H_

#include "attribute_types/attribute_type.h"

#include <string>
#include <map>
#include <vector>

namespace gui
{

class Object
{
public:
    // Constructors/Destructor
    Object(std::string name, std::string id,  Object* parent);

    // Functions
    virtual void Update() = 0;

    bool SetAttributeValue(const std::string name, const std::string value);
    AttributeType* GetAttribute(const std::string name) const;
    bool HasAttribute(const std::string name) const;

    bool HasParent();

    std::shared_ptr<Object> GetChild(
        const std::string id,
        bool recursive) const;
    void AddChild(std::shared_ptr<Object> child);

    std::string GetID() const;

protected:
    // Variables
    std::string name_;
    std::string id_;
    Object* parent_;

    std::map<std::string, AttributeType*> attribute_list_ = { };
    std::vector<std::shared_ptr<Object>> child_objects_ = { };

    // Functions
    void UpdateChilds();
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_OBJECT_H_
