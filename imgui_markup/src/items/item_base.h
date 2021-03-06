#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_BASE_H_

#include "items/item_mapping.h"
#include "items/item_api.h"
#include "attribute_types/attribute_base.h"
#include "attribute_types/float2.h"
#include "parser/parser_result.h"

#include <string>
#include <map>
#include <vector>
#include <memory>

namespace igm::internal
{

namespace parser
{
class Interpreter;  // Used as a friend class
}

class ItemBase : public ItemAPI
{
public:
    /**
     * @param[in] type   - Type of the item
     * @param[in] id     - ID of the item
     * @param[in] parent - Pointer to the parent item, nullptr
     *                     if the item has no parent item.
    */
    ItemBase(
        ItemType type,
        ItemCategory category,
        std::string id,
        ItemBase* parent);

    ItemBase(const ItemBase&) = delete;

    /**
     * Main update function that should be called every frame.
     */
    void Update(Float2 position, Float2 size);

    /**
     * Get a pointer to an attribute from this item by its name.
     *
     * @param[in] name - The name of the attribtue.
     *
     * @return a pointer to the attribute. nullptr, if the attribute with the
     *         given name does not exists.
    */
    AttributeBase* GetAttribute(const std::string name) const;

    inline void SetParent(ItemBase* parent) { this->parent_ = parent; }

    inline std::string GetID()        const { return this->access_id_; }
    inline ItemType GetType()         const { return this->type_;      }
    inline ItemCategory GetCategory() const { return this->category_;  }
    inline ItemBase* GetParent()      const { return this->parent_;    }
    inline Float2 GetSize()           const { return this->size_;      }
    inline Float2 GetPosition()       const { return this->position_;  }

protected:
    ItemType type_;
    ItemCategory category_;

    /**
     * Pointer to the items parent. nullptr if this item is the
     * root item  and has no parent item.
     */
    ItemBase* parent_;

    /**
     * Full object ID that is set through the markup language,
     * which enables access from the backend.
     * The string is empty when the item's ID is not set.
     */
    std::string access_id_;

    /**
     * Unique ID of the item, which is generated by the constructor.
     * The ID is usually the object's address, converted to a string.
     */
    std::string draw_id_;

    /**
     * Position of the object, which is also used as the ImGui position
     * to draw the object.
     */
    Float2 position_;

    /**
     * Size of the item, set by the item's update function.
     */
    Float2 size_;  // Size of the item, set by the item itself

    /**
     * Shared pointer to every child item.
     * These are the main pointers managing the child items.
     */
    std::vector<std::shared_ptr<ItemBase>> child_items_ = { };

    /**
     * List of the item attributes that can be set through
     * the markup language.
     * Use functions AddAttribute() and RemoveAttribute() to edit the
     * attribute list.
     */
    std::map<std::string, AttributeBase*> attribute_list_ = { };

    // Functions
    virtual void IMPL_Update(Float2 position, Float2 size) { };

    /**
     * Add an attribute to the attribute list.
     *
     * @param[in] name - The name of the attribute, that can be used to
     *                   access the attribute from data that is parsed.
     * @param[in] attribute - An pointer to the attribute.
    */
    void AddAttribute(const std::string name, AttributeBase* attribute);

    /**
     * Remove an attribute from the attribute list.
     * Used to remove the default attributes that are added
     * by this class.
     *
     * @param[in] name - The name of the attribute that will be removed.
    */
    void RemoveAttribute(const std::string name);

private:
    friend class parser::Interpreter;

    /**
     * Adds an child item to the child_items_ variable.
     */
    void AddChild(std::shared_ptr<ItemBase> child);

    /**
     * Function that is called by the interpreter before the interpreter
     * starts the process of the items child nodes.
     * This can be used to e.g. add attributes to its parent item.
     *
     * @param[in] error_message - String that will be set to the error message
     *                            if there is one.
     */
    virtual bool OnProcessStart(std::string& error_message) { return true; }

    /**
     * Function that is called by the interpreter after the interpreter
     * processed the items child nodes.
     * This can be used to e.g. add attributes to its child items or
     * to make sure that specific attributes are set.
     *
     * @param[in] error_message - String that will be set to the error message
     *                            if there is one.
     */
    virtual bool OnProcessEnd(std::string& error_message) { return true; }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_BASE_H_
