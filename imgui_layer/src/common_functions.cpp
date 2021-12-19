#include "ilpch.h"
#include "imgui_layer/common_functions.h"

#include "imgui_layer/parser/parser.h"

namespace gui
{

ParserResult ParseFile(const char* path, GlobalObject& global_object)
{
    // NOTE: This will be changed during the rework of the
    // entire parsing system.

    //if (!gui::FileManager::LoadFromFile(path, global_object))
    //    return gui::FileManager::GetLastError();

    return ParserResult(ParserResultType::kSuccess);
}

}  // namespace gui
