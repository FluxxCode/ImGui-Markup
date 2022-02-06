#include "impch.h"
#include "imgui_markup.h"

#include "common/file_stack.h"
#include "common/file_context.h"

namespace imgui_markup
{

size_t ParseFile(const char* path, bool* result)
{
    bool temp_result;
    return internal::FileStack::ParseFile(path, result ? *result : temp_result);
}

void FreeContext(const size_t id, bool* result)
{
    bool temp_result;
    internal::FileStack::FreeContext(id, result ? *result : temp_result);
}

Result GetLastResult(const size_t id, bool* result)
{
    bool temp_result;
    return internal::FileStack::GetLastResult(
        id, result ? *result : temp_result);
}

void Update(const size_t id, bool* result_out)
{
    bool result;

    internal::FileContext* context =
        internal::FileStack::GetFileContext(id, result);

    if (!result)
    {
        if (result_out)
            *result_out = result;
        return;
    }

    for (auto& child : context->object_tree_)
        child->Update();
}

}  // namespace imgui_markup
