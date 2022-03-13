#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_MAPPING_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_MAPPING_H_

#include <map>  // std::map

namespace imgui_markup::internal
{

enum class ItemCategory : unsigned char
{
    kContainer,  // Panel, ChildPanel, Container...
    kView,       // StackView...
    kDrawable,   // Button, Text, Checkbox...
    kStyle,      // ButtonStyle, PanelStyle...
    kOther       // Attribute types...
};

enum class ItemType : unsigned char
{
    kUndefined,

    // Container
    kPanel,
    kChildPanel,
    kContainer,

    // Views
    kStackView,

    // Drawables
    kText,
    kButton,
    kCheckbox,

    // Styles
    kButtonStyle,
    kPanelStyle,

    // Other
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
    // Container
    { "Panel",          ItemType::kPanel      },
    { "ChildPanel",     ItemType::kChildPanel },
    { "Container",      ItemType::kContainer  },

    // Views
    { "StackView",      ItemType::kStackView },

    // Drawables
    { "Text",           ItemType::kText     },
    { "Button",         ItemType::kButton   },
    { "Checkbox",       ItemType::kCheckbox },

    // Styles
    { "PanelStyle",     ItemType::kPanelStyle  },
    { "ButtonStyle",    ItemType::kButtonStyle },

    { "Bool",           ItemType::kItemBool   },
    { "Float",          ItemType::kItemFloat  },
    { "Float2",         ItemType::kItemFloat2 },
    { "Float3",         ItemType::kItemFloat3 },
    { "Float4",         ItemType::kItemFloat4 },
    { "Int",            ItemType::kItemInt    },
    { "String",         ItemType::kItemString }
};

}  // namespace imgui_markup::internal::item_types

bool StringToItemType(std::string str, ItemType& out);
std::string ItemTypeToString(ItemType obj);

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_MAPPING_H_
