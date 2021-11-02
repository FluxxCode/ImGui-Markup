#ifndef IMGUI_LAYER_SRC_OBJECTS_GLOBAL_OBJECT_H_
#define IMGUI_LAYER_SRC_OBJECTS_GLOBAL_OBJECT_H_

#include "objects/object.h"

#include "attribute_types/string.h"

namespace gui
{

class GlobalObject : public Object
{
public:
    // Constructors/Destructors
    GlobalObject();

    // Functions
    void Update();

    /**
     * Resets every attribute from this object.
    */
    void Reset();

    // Variables
    String version_;
    String description_;
    String author_;
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_GLOBAL_OBJECT_H_
