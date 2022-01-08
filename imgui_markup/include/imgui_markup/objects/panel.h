#ifndef IMGUI_MARKUP_SRC_OBJECTS_PANEL_H_
#define IMGUI_MARKUP_SRC_OBJECTS_PANEL_H_

#include "imgui_markup/objects/common/object.h"

#include "imgui_markup/attribute_types/string.h"
#include "imgui_markup/attribute_types/float2.h"

namespace imgui_markup
{

class Panel : public Object
{
public:
    // Constructor/Destructor
    Panel(std::string id, Object* parent);

    Panel& operator=(const Panel& other);

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

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_SRC_OBJECTS_PANEL_H_
