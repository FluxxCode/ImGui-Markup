#ifndef IMGUI_MARKUP_SRC_COMMON_FILE_STACK_H_
#define IMGUI_MARKUP_SRC_COMMON_FILE_STACK_H_

#include "common/file_context.h"
#include "result.h"

#include <string>

namespace imgui_markup::internal
{

/**
 * Main file stack that stores all loaded trees and their contexts.
 */
class FileStack
{
public:
    FileStack(const FileStack&) = delete;
    void operator=(FileStack const&) = delete;

    /**
     * Parses a file containing the valid markup language used of the layer and
     * pushes it to the main file_contexts stack.
     *
     * @param[in] path - The path to the file that will get loaded.
     *                   Absolute and relative paths are allowed.
     * @return ID of the loaded file context.
     *         An ID of 0 is invalid and means that an error occurred while
     *         parsing the file.
    */
    static size_t ParseFile(const std::string file, bool& result);

    /**
     * Deletes both file context and result of a specific context.
     */
    static void FreeContext(const size_t id, bool& result);

    /**
     * Get the last result of a specific context.
     */
    static Result GetLastResult(const size_t id, bool& result);

    /**
     * Get a specific file context.
     * nullptr is returned when the id is invalid and
     * the context not exists.
     */
    static FileContext* GetFileContext(const size_t id, bool& result);

    /**
     * Get an ObjectAPI of a specific object from a context.
     */
    static ObjectAPI* GetObjectAPI(
        const size_t id, const std::string object_id);

private:
    /**
     * Main buffer containing the loaded object trees and their file context.
     */
    std::map<size_t, FileContext> file_contexts_;
    std::map<size_t, Result> last_results_;

    size_t context_count = 0;

    FileStack();
    static FileStack& Get();

    size_t IMPL_ParseFile(const std::string file, bool& result);
    void IMPL_FreeContext(const size_t id, bool& result);
    Result IMPL_GetLastResult(const size_t id, bool& result) const;
    FileContext* IMPL_GetFileContext(const size_t id, bool& Result);
    ObjectAPI* IMPL_GetObjectAPI(const size_t id, const std::string object_id);
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_COMMON_FILE_STACK_H_
