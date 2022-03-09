#ifndef IMGUI_MARKUP_SRC_OBJECTS_COMMON_OBJECT_MAPPING_H_
#define IMGUI_MARKUP_SRC_OBJECTS_COMMON_OBJECT_MAPPING_H_

#include <map>  // std::map

namespace imgui_markup::internal
{

enum class ObjectType : unsigned char
{
    kUndefined,
    kPanel,
    kPanelStyle,
    kText,
    kButton,
    kButtonStyle,
    kCheckbox,
    kChildPanel,
    kContainer,

    kObjectBool,
    kObjectFloat,
    kObjectFloat2,
    kObjectFloat3,
    kObjectFloat4,
    kObjectInt,
    kObjectString,
};

namespace object_types
{

const std::map<std::string, ObjectType> object_mapping =
{
    { "Panel",          ObjectType::kPanel          },
    { "PanelStyle",     ObjectType::kPanelStyle     },
    { "Text",           ObjectType::kText           },
    { "Button",         ObjectType::kButton         },
    { "ButtonStyle",    ObjectType::kButtonStyle    },
    { "Checkbox",       ObjectType::kCheckbox       },
    { "ChildPanel",     ObjectType::kChildPanel     },
    { "Container",      ObjectType::kContainer      },
    { "Bool",           ObjectType::kObjectBool     },
    { "Float",          ObjectType::kObjectFloat    },
    { "Float2",         ObjectType::kObjectFloat2   },
    { "Float3",         ObjectType::kObjectFloat3   },
    { "Float4",         ObjectType::kObjectFloat4   },
    { "Int",            ObjectType::kObjectInt      },
    { "String",         ObjectType::kObjectString   }
};

}  // namespace imgui_markup::internal::object_types

bool StringToObjectType(std::string str, ObjectType& out);
std::string ObjectTypeToString(ObjectType obj);

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_OBJECTS_COMMON_OBJECT_MAPPING_H_
