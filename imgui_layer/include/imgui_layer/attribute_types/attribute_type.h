#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_

#include "imgui_layer/parser/parser_error.h"

#include <string>

namespace gui
{

class AttributeType
{
public:
    // Variables
    bool value_changed_ = false;

    // Functions
    bool LoadValue(std::string value);
    virtual bool IMPLLoadValue(std::string value) = 0;

    /**
     * Gets a child attributeby its ID.
     * Used for the attribute types like float2, float3, float4 that
     * have the child attributes x,y,z,w.
     *
     * @param[in] id - The name of the child attribute, e.g. x,y,z or w.
     *
     * @return pointer to the child attribute, nullptr if the child attribute
     *         does not exists.
    */
    virtual AttributeType* GetChild(std::string name);

    /**
     * Checks if the attribute has a child attributes with the given name.
     *
     * @param[in] name - The name of the child attribute that will be checked.
     *
     * @return true if the child attribute exists, false if the attribute
     *         has no child attributes with the given name.
    */
    virtual bool HasChild(std::string name);

    virtual std::string ToString() = 0;

    ParserError GetLastError() const;

protected:
    // Variables
    ParserError last_error_;
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
