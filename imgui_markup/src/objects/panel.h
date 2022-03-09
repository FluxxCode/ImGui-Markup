#ifndef IMGUI_MARKUP_SRC_OBJECTS_PANEL_H_
#define IMGUI_MARKUP_SRC_OBJECTS_PANEL_H_

#include "objects/common/object_base.h"
#include "objects/common/window_flags.h"

#include "attribute_types/bool.h"
#include "attribute_types/string.h"
#include "attribute_types/float2.h"

namespace imgui_markup::internal
{

class PanelStyle;

class Panel : public ObjectBase, public WindowFlags
{
public:
    // Constructor/Destructor
    Panel(std::string id, ObjectBase* parent);
    Panel(const Panel&) = delete;

    Float2 position_overwrite_;
    Float2 size_overwrite_;
    String title_;

    // Flags
    Bool no_title_bar_ = false;
    Bool no_resize_    = false;

private:
    friend class PanelStyle;
    PanelStyle* style_ = nullptr;

    bool is_hovered_ = false;

    bool init_attributes_ = true;
    void InitAttributes(Float2 position, Float2 size);

    // See object.h for documentation
    void IMPL_Update(Float2 position, Float2 size);
    bool OnProcessStart(std::string& error_message);
    bool OnProcessEnd(std::string& error_message);

    // See object_api.h for documentation
    Bool API_IsPressed(MouseButton button) const;
    Bool API_IsHovered() const;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_OBJECTS_PANEL_H_
