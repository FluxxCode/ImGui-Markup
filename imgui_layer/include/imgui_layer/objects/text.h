#ifndef IMGUI_LAYER_SRC_OBJECTS_TEXT_H_
#define IMGUI_LAYER_SRC_OBJECTS_TEXT_H_

#include "imgui_layer/objects/common/object.h"

#include "imgui_layer/attribute_types/float4.h"
#include "imgui_layer/attribute_types/float2.h"
#include "imgui_layer/attribute_types/string.h"

namespace gui
{

class Text : public Object
{
public:
    // Constructor/Destructor
    Text(std::string id, Object* parent);

    Text& operator=(const Text& other);

    // Functions
    void Update();

    String text_;
    Float4 color_;
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_TEXT_H_
