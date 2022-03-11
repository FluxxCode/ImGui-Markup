#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_LIST_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_LIST_H_

#include "items/common/item_base.h"
#include "items/common/item_mapping.h"

#include "items/panel.h"
#include "items/panel_style.h"
#include "items/child_panel.h"
#include "items/button.h"
#include "items/button_style.h"
#include "items/text.h"
#include "items/checkbox.h"
#include "items/container.h"
#include "items/attribute_types/item_bool.h"
#include "items/attribute_types/item_float.h"
#include "items/attribute_types/item_float2.h"
#include "items/attribute_types/item_float3.h"
#include "items/attribute_types/item_float4.h"
#include "items/attribute_types/item_int.h"
#include "items/attribute_types/item_string.h"

#include <memory>      // shared_ptr
#include <map>         // map
#include <functional>  // function

namespace imgui_markup::internal
{

class ItemList
{
public:
    // Constructors/Destructors
    ItemList(const ItemList&) = delete;

    // Operator
    void operator=(ItemList const&) = delete;

    // Functions
    /**
     * Create a new item on the heap.
     *
     * @param[in] type   - The type of the item that will be created.
     *                     Only types that are specified in the item_list_
     *                     are allowed. An empty string is not allowed.
     * @param[in] id     - The ID that the item will get. The string can be
     *                     empty if the item should not get an ID.
     * @param[in] parent - A pointer to the parent item. It can be a nullptr,
     *                     if the item has no parent obejct.
     *
     * @return A shared_ptr to the created item on the heap.
     *         Nullptr will be returned if the item was not created because
     *         the given type does not exists in the item_list_.
    */
    static std::shared_ptr<ItemBase> CreateItem(
        std::string type,
        std::string id,
        ItemBase* parent);

    /**
     * Checks if the given type is defined in the item_list_.
     *
     * @param[out] converted_type - Buffer receiving the converted item type.
     *
     * @return true if the type exists and an item with the type can be
     *         be created, false if there is no item of the given type.
    */
    static bool IsDefined(
        std::string type,
        ItemType* converted_type = nullptr);

private:
    // Constructor
    ItemList() { };

    // Variables
    /**
     * This is the main item_list_, containing the types and function
     * pointers to create an instance of an item.
    */
    const std::map<ItemType, std::function<std::shared_ptr<ItemBase>(
        std::string, ItemBase*)>> item_list_ = {
            { ItemType::kPanel,       CreateItemInstance<Panel>        },
            { ItemType::kPanelStyle,  CreateItemInstance<PanelStyle>   },
            { ItemType::kChildPanel,  CreateItemInstance<ChildPanel>   },
            { ItemType::kButton,      CreateItemInstance<Button>       },
            { ItemType::kButtonStyle, CreateItemInstance<ButtonStyle>  },
            { ItemType::kText,        CreateItemInstance<Text>         },
            { ItemType::kCheckbox,    CreateItemInstance<Checkbox>     },
            { ItemType::kContainer,   CreateItemInstance<Container>    },

            // Atribute types
            { ItemType::kItemBool,   CreateItemInstance<ItemBool>   },
            { ItemType::kItemFloat,  CreateItemInstance<ItemFloat>  },
            { ItemType::kItemFloat2, CreateItemInstance<ItemFloat2> },
            { ItemType::kItemFloat3, CreateItemInstance<ItemFloat3> },
            { ItemType::kItemFloat4, CreateItemInstance<ItemFloat4> },
            { ItemType::kItemInt,    CreateItemInstance<ItemInt>    },
            { ItemType::kItemString, CreateItemInstance<ItemString> }
    };

    // Functions
    static ItemList& Get();

    std::shared_ptr<ItemBase> IMPLCreateItem(
        std::string type,
        std::string id,
        ItemBase* parent);

    bool IMPLIsDefined(std::string type, ItemType* converted_type);

    template<typename T>
    static std::shared_ptr<T> CreateItemInstance(
        std::string id,
        ItemBase* parent)
    {
        return std::make_shared<T>(id, parent);
    }
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_LIST_H_
