#include "impch.h"
#include "common/file_stack.h"

#include "parser/parser.h"

namespace imgui_markup::internal
{

size_t FileStack::ParseFile(const std::string file, bool* result)
{
    return FileStack::Get().IMPL_ParseFile(file, result);
}

void FileStack::FreeContext(const size_t id, bool* result)
{
    return FileStack::Get().IMPL_FreeContext(id, result);
}

Result FileStack::GetLastResult(const size_t id, bool* result)
{
    return FileStack::Get().IMPL_GetLastResult(id, result);
}

FileContext* FileStack::GetFileContext(const size_t id, bool* result)
{
    return FileStack::Get().IMPL_GetFileContext(id, result);
}

ItemAPI* FileStack::GetItemAPI(const size_t id, const std::string item_id)
{
    return FileStack::Get().IMPL_GetItemAPI(id, item_id);
}

FileStack::FileStack()
{ }

FileStack& FileStack::Get()
{
    static FileStack instance;
    return instance;
}

size_t FileStack::IMPL_ParseFile(const std::string file, bool* result)
{
    if (result)
        *result = false;

    this->context_count++;

    parser::Parser parser;
    FileContext context;

    ParserResult parser_result = parser.ParseFile(file, context);
    if (parser_result.type_ != ParserResultType::kSuccess)
    {
        this->file_contexts_[context_count] = FileContext();
        this->last_results_[context_count] =
            Result(ResultType::kParserError, parser_result.ToString().c_str());

        return context_count;
    }

    this->file_contexts_[context_count] = context;

    if (result)
        *result = true;

    return context_count;
}

void FileStack::IMPL_FreeContext(const size_t id, bool* result)
{
    if (result)
        *result = false;

    if (this->file_contexts_.find(id) == this->file_contexts_.end())
        return;

    if (result)
        *result = true;

    this->file_contexts_.erase(id);
    this->last_results_.erase(id);
}

Result FileStack::IMPL_GetLastResult(const size_t id, bool* result) const
{
    if (result)
        *result = false;

    if (this->last_results_.find(id) == this->last_results_.end())
        return Result();

    if (result)
        *result = true;

    return this->last_results_.at(id);
}

FileContext* FileStack::IMPL_GetFileContext(const size_t id, bool* result)
{
    if (result)
        *result = false;

    if (this->file_contexts_.find(id) == this->file_contexts_.end())
    {
        this->last_results_[id] =
            Result(ResultType::kInvalidContextID, "InvalidContextID");

        return nullptr;
    }

    if (result)
        *result = true;

    return &this->file_contexts_.at(id);
}

ItemAPI* FileStack::IMPL_GetItemAPI(
    const size_t id, const std::string item_id)
{
    bool result;
    FileContext* context = this->IMPL_GetFileContext(id, &result);

    if (!result)
        return nullptr;

    if (context->item_references_.find(item_id) ==
        context->item_references_.end())
    {
        this->last_results_[id] =
            Result(ResultType::kInvalidItemID, "InvalidItemID");

        return nullptr;
    }

    return dynamic_cast<ItemAPI*>(&context->item_references_.at(item_id));
}

}  // namespace imgui_markup::internal
