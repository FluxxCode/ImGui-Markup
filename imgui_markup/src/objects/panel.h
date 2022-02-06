#ifndef IMGUI_MARKUP_SRC_OBJECTS_PANEL_H_
#define IMGUI_MARKUP_SRC_OBJECTS_PANEL_H_

#include "objects/common/object_base.h"
#include "objects/common/window_flags.h"

#include "attribute_types/bool.h"
#include "attribute_types/string.h"
#include "attribute_types/float2.h"

namespace imgui_markup::internal{

class PanelStyle;

class Panel : public ObjectBase, public WindowFlags
{
public:
    // Constructor/Destructor
    Panel(std::string id, ObjectBase* parent);

    Panel& operator=(const Panel& other);

    // Functions
    void Update();

    String title_;

    // Flags
    Bool no_title_bar_ = false;
    Bool no_resize_    = false;

private:
    friend class PanelStyle;

    PanelStyle* style_ = nullptr;

    bool init_panel_attributes_ = true;
    void InitPanelAttributes();

    // See object.h for documentation
    bool OnProcessStart(std::string& error_message);
    bool OnProcessEnd(std::string& error_message);
};

}  // namespace imgui_markup::internal
#endif  // IMGUI_MARKUP_SRC_OBJECTS_PANEL_H_
