#ifndef IMGUI_MARKUP_SRC_OBJECTS_OBJECT_LIST_H_
#define IMGUI_MARKUP_SRC_OBJECTS_OBJECT_LIST_H_

#include "objects/common/object_base.h"

#include "objects/panel.h"
#include "objects/panel_style.h"
#include "objects/child_panel.h"
#include "objects/button.h"
#include "objects/button_style.h"
#include "objects/text.h"
#include "objects/container.h"
#include "objects/attribute_types/object_bool.h"
#include "objects/attribute_types/object_float.h"
#include "objects/attribute_types/object_float2.h"
#include "objects/attribute_types/object_float3.h"
#include "objects/attribute_types/object_float4.h"
#include "objects/attribute_types/object_int.h"
#include "objects/attribute_types/object_string.h"

#include <memory>      // shared_ptr
#include <map>         // map
#include <functional>  // function

namespace imgui_markup::internal
{

class ObjectList
{
public:
    // Constructors/Destructors
    ObjectList(const ObjectList&) = delete;

    // Operator
    void operator=(ObjectList const&) = delete;

    // Functions
    /**
     * Create a new object on the heap.
     *
     * @param[in] type   - The type of the object that will be created.
     *                     Only types that are specified in the object_list_
     *                     are allowed. An empty string is not allowed.
     * @param[in] id     - The ID that the object will get. The string can be
     *                     empty if the object should not get an ID.
     * @param[in] parent - A pointer to the parent object. It can be a nullptr,
     *                     if the object has no parent obejct.
     *
     * @return A shared_ptr to the created object on the heap.
     *         Nullptr will be returned if the object was not created because
     *         the given type does not exists in the object_list_.
    */
    static std::shared_ptr<ObjectBase> CreateObject(
        std::string type,
        std::string id,
        ObjectBase* parent);

    /**
     * Checks if the given type is defined in the object_list_.
     *
     * @return true if the type exists and an object with the type can be
     *         be created, false if there is no object of the given type.
    */
    static bool IsDefined(std::string type);

private:
    // Constructor
    ObjectList() { };

    // Variables
    /**
     * This is the main object_list_, containing the types and function
     * pointers to create an instance of an object.
    */
    const std::map<std::string, std::function<std::shared_ptr<ObjectBase>(
        std::string, ObjectBase*)>> object_list_ = {
            { "Panel",       CreateObjectInstance<Panel>        },
            { "PanelStyle",  CreateObjectInstance<PanelStyle>   },
            { "ChildPanel",  CreateObjectInstance<ChildPanel>   },
            { "Button",      CreateObjectInstance<Button>       },
            { "ButtonStyle", CreateObjectInstance<ButtonStyle>  },
            { "Text",        CreateObjectInstance<Text>         },
            { "Container",   CreateObjectInstance<Container>    },

            // Atribute types
            { "Bool",        CreateObjectInstance<ObjectBool>   },
            { "Float",       CreateObjectInstance<ObjectFloat>  },
            { "Float2",      CreateObjectInstance<ObjectFloat2> },
            { "Float3",      CreateObjectInstance<ObjectFloat3> },
            { "Float4",      CreateObjectInstance<ObjectFloat4> },
            { "Int",         CreateObjectInstance<ObjectInt>    },
            { "String",      CreateObjectInstance<ObjectString> }
    };

    // Functions
    static ObjectList& Get();

    std::shared_ptr<ObjectBase> IMPLCreateObject(
        std::string type,
        std::string id,
        ObjectBase* parent);

    bool IMPLIsDefined(std::string type);

    template<typename T>
    static std::shared_ptr<T> CreateObjectInstance(
        std::string id,
        ObjectBase* parent)
    {
        return std::make_shared<T>(id, parent);
    }
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_OBJECTS_OBJECT_LIST_H_
