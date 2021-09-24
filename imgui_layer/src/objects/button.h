#ifndef IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_
#define IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_

#include "objects/object.h"

#include "attribute_types/float2.h"
#include "attribute_types/float4.h"
#include "attribute_types/string.h"

namespace gui
{

class IMGUI_LAYER_API Button : public Object
{
public:
    // Constructor/Destructor
    Button(std::string id, Object* parent);

    // Functions
    void Update();

    Float2 pos_;
    Float2 size_;
    Float4 color_;
    Float4 color_active_;
    Float4 color_hovered_;
    String text_;
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_
