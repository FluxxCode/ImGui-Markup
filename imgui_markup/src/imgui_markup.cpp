#include "impch.h"
#include "imgui_markup.h"

#include "input.h"
#include "common/file_stack.h"
#include "common/file_context.h"
#include "objects/common/object_api.h"
#include "attribute_types/float2.h"

#include <assert.h>

namespace imgui_markup
{

size_t ParseFile(const char* path, bool* result)
{
    return internal::FileStack::ParseFile(path, result);
}

void FreeContext(const size_t id, bool* result)
{
    internal::FileStack::FreeContext(id, result);
}

Result GetLastResult(const size_t id, bool* result)
{
    bool temp_result;
    return internal::FileStack::GetLastResult(id, result);
}

void Update(const size_t id, bool* result)
{
    internal::FileContext* context =
        internal::FileStack::GetFileContext(id, result);

    if (!context)
        return;

    for (auto& child : context->object_tree_)
        child->Update(internal::Float2(0, 0));
}

bool IsPressed(
    size_t context_id, std::string object_id, MouseButton button, bool* result)
{
    internal::ObjectAPI* api =
        internal::FileStack::GetObjectAPI(context_id, object_id);

    if (!api)
        return false;

    return api->API_IsPressed(button);
}

bool IsHovered(size_t context_id, std::string object_id, bool* result)
{
    internal::ObjectAPI* api =
        internal::FileStack::GetObjectAPI(context_id, object_id);

    if (!api)
        return false;

    return api->API_IsHovered();
}

bool IsToggled(size_t context_id, std::string object_id, bool* result)
{
    internal::ObjectAPI* api =
        internal::FileStack::GetObjectAPI(context_id, object_id);

    if (!api)
        return false;

    return api->API_IsToggled();
}

}  // namespace imgui_markup
