#ifndef IMGUI_LAYER_INCLUDE_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
#define IMGUI_LAYER_INCLUDE_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_

#include "imgui_layer/parser/parser_result.h"

#include <string>

namespace gui
{

enum class AttributeType
{
    kBool,
    kFloat,
    kFloat2,
    kFloat3,
    kFloat4,
    kInt,
    kString
};

struct Attribute
{
    Attribute(AttributeType type);

    AttributeType type;

    /**
     * Will be set when the LoadValue function was sucessfully called.
     */
    bool value_changed_ = false;

    /**
     * Loads a string value into the attribute type.
     *
     * @param value that will be loaded into the attribute.
     * @return true on sucess
     * @return false if there was a conversion error
     */
    bool LoadValue(std::string value);
    virtual bool IMPL_LoadValue(std::string value) = 0;

    /**
     * Converts the attribute value type to a std::string.
     */
    virtual std::string ToString() const = 0;
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
