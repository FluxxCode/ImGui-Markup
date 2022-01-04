#ifndef IMGUI_LAYER_SRC_OBJECTS_PANEL_H_
#define IMGUI_LAYER_SRC_OBJECTS_PANEL_H_

#include "imgui_layer/objects/common/object.h"

#include "imgui_layer/attribute_types/string.h"
#include "imgui_layer/attribute_types/float2.h"

#include "imgui.h"

namespace gui
{

class Panel : public Object
{
public:
    // Constructor/Destructor
    Panel(std::string id, Object* parent);

    // Functions
    void Update();

    String title_;

private:
    bool init_panel_attributes_ = true;

    void InitPanelAttributes();

    // See object.h for documentation
    bool Validate(std::string& error_message) const;
    bool OnProcessEnd(std::string& error_message);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_PANEL_H_
