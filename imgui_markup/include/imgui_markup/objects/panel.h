#ifndef IMGUI_MARKUP_SRC_OBJECTS_PANEL_H_
#define IMGUI_MARKUP_SRC_OBJECTS_PANEL_H_

#include "imgui_markup/objects/common/object.h"
#include "imgui_markup/objects/common/window_flags.h"

#include "imgui_markup/attribute_types/bool.h"
#include "imgui_markup/attribute_types/string.h"
#include "imgui_markup/attribute_types/float2.h"

namespace imgui_markup
{

class Panel : public Object, public WindowFlags
{
public:
    // Constructor/Destructor
    Panel(std::string id, Object* parent);

    Panel& operator=(const Panel& other);

    // Functions
    void Update();

    String title_;

    // Flags
    Bool no_title_bar_ = false;
    Bool no_resize_    = false;

private:
    bool init_panel_attributes_ = true;

    void InitPanelAttributes();

    // See object.h for documentation
    bool OnProcessStart(std::string& error_message);
    bool OnProcessEnd(std::string& error_message);
};

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_SRC_OBJECTS_PANEL_H_
