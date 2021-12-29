#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_

#include "imgui_layer/attribute_types/attribute_type.h"
#include "imgui_layer/attribute_types/float.h"

#include <string>

namespace gui
{

class Float4 : public AttributeType
{
public:
    // Variables
    Float x = 0;
    Float y = 0;
    Float z = 0;
    Float w = 0;

    // Constructors
    Float4();
    Float4(float x, float y, float z, float w);
    Float4(ImVec4 vec);

    // Functions
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
    AttributeType* GetChild(std::string name);

    /**
     * Checks if the attribute has a child attributes with the given name.
     *
     * @param[in] name - The name of the child attribute that will be checked.
     *
     * @return true if the child attribute exists, false if the attribute
     *         has no child attributes with the given name.
    */
    bool HasChild(std::string name);

    std::string ToString() const;

    // Operator
    operator ImVec4();

private:
    // Functions
    bool IMPLLoadValue(std::string value);

    void SetError(std::string value);
    void SetError(std::string value, Float& child);

    void ResetValues();
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_
