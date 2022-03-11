#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_MAPPING_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_MAPPING_H_

#include <map>  // std::map

namespace imgui_markup::internal
{

enum class ItemCategory : unsigned char
{
    kDrawable,   // Button, Text, Checkbox...
    kContainer,  // Panel, ChildPanel, Container...
    kView,       // StackView...
    kStyle,      // ButtonStyle, PanelStyle...
    kOther       // Attribute types...
};

enum class ItemType : unsigned char
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

    kItemBool,
    kItemFloat,
    kItemFloat2,
    kItemFloat3,
    kItemFloat4,
    kItemInt,
    kItemString,
};

namespace item_types
{

const std::map<std::string, ItemType> item_mapping =
{
    { "Panel",          ItemType::kPanel          },
    { "PanelStyle",     ItemType::kPanelStyle     },
    { "Text",           ItemType::kText           },
    { "Button",         ItemType::kButton         },
    { "ButtonStyle",    ItemType::kButtonStyle    },
    { "Checkbox",       ItemType::kCheckbox       },
    { "ChildPanel",     ItemType::kChildPanel     },
    { "Container",      ItemType::kContainer      },
    { "Bool",           ItemType::kItemBool     },
    { "Float",          ItemType::kItemFloat    },
    { "Float2",         ItemType::kItemFloat2   },
    { "Float3",         ItemType::kItemFloat3   },
    { "Float4",         ItemType::kItemFloat4   },
    { "Int",            ItemType::kItemInt      },
    { "String",         ItemType::kItemString   }
};

}  // namespace imgui_markup::internal::item_types

bool StringToItemType(std::string str, ItemType& out);
std::string ItemTypeToString(ItemType obj);

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_MAPPING_H_
