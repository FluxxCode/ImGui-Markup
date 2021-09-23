#ifndef IMGUI_LAYER_SRC_OBJECTS_OBJECT_LIST_H_
#define IMGUI_LAYER_SRC_OBJECTS_OBJECT_LIST_H_

#include "objects/object.h"

#include "objects/panel.h"
#include "objects/button.h"

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
    static std::shared_ptr<Object> CreateObject(
        std::string type,
        std::string id,
        Object* parent);

    static bool IsDefined(std::string type);

private:
    // Constructor
    ObjectList() { };

    // Variables
    const std::map<std::string, std::function<std::shared_ptr<Object>(
        std::string, Object*)>> object_list_ = {
            { "Panel", CreateObjectInstance<Panel> },
            { "Button", CreateObjectInstance<Button> }
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
