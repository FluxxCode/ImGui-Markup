#include "imgui_layer/common_functions.h"

#include "imgui_layer/parser/file_manager.h"

namespace gui
{

ParserError ParseFile(const char* path, GlobalObject& global_object)
{
    // NOTE: This will be changed during the rework of the
    // entire parsing system.
    if (!gui::FileManager::LoadFromFile(path, global_object))
        return gui::FileManager::GetLastError();

    return ParserError(ParserErrorType::kSuccess, "Success");
}

}  // namespace gui
