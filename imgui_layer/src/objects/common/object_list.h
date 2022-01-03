#ifndef IMGUI_LAYER_SRC_OBJECTS_OBJECT_LIST_H_
#define IMGUI_LAYER_SRC_OBJECTS_OBJECT_LIST_H_

#include "imgui_layer/objects/common/object.h"

#include "imgui_layer/objects/panel.h"
#include "imgui_layer/objects/child_panel.h"
#include "imgui_layer/objects/button.h"
#include "imgui_layer/objects/text.h"
#include "imgui_layer/objects/container.h"
#include "imgui_layer/objects/attribute_types/object_bool.h"
#include "imgui_layer/objects/attribute_types/object_float.h"
#include "imgui_layer/objects/attribute_types/object_float2.h"
#include "imgui_layer/objects/attribute_types/object_float3.h"
#include "imgui_layer/objects/attribute_types/object_float4.h"
#include "imgui_layer/objects/attribute_types/object_int.h"
#include "imgui_layer/objects/attribute_types/object_string.h"

#include <memory>
#include <map>
#include <functional>

namespace gui
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
    static std::shared_ptr<Object> CreateObject(
        std::string type,
        std::string id,
        Object* parent);

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
    const std::map<std::string, std::function<std::shared_ptr<Object>(
        std::string, Object*)>> object_list_ = {
            { "Panel",      CreateObjectInstance<Panel>        },
            { "ChildPanel", CreateObjectInstance<ChildPanel>   },
            { "Button",     CreateObjectInstance<Button>       },
            { "Text",       CreateObjectInstance<Text>         },
            { "Container",  CreateObjectInstance<Container>    },

            // Atribute types
            { "Bool",       CreateObjectInstance<ObjectBool>   },
            { "Float",      CreateObjectInstance<ObjectFloat>  },
            { "Float2",     CreateObjectInstance<ObjectFloat2> },
            { "Float3",     CreateObjectInstance<ObjectFloat3> },
            { "Float4",     CreateObjectInstance<ObjectFloat4> },
            { "Int",        CreateObjectInstance<ObjectInt>    },
            { "String",     CreateObjectInstance<ObjectString> }
    };

    // Functions
    static ObjectList& Get();

    std::shared_ptr<Object> IMPLCreateObject(
        std::string type,
        std::string id,
        Object* parent);

    bool IMPLIsDefined(std::string type);

    template<typename T>
    static std::shared_ptr<T> CreateObjectInstance(
        std::string id,
        Object* parent)
    {
        return std::make_shared<T>(id, parent);
    }
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_OBJECT_LIST_H_
