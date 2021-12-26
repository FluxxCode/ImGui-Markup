#include "ilpch.h"
#include "imgui_layer/common_functions.h"

#include "imgui_layer/parser/parser.h"

namespace gui
{

ParserResult ParseFile(const char* path, GlobalObject& global_object)
{
    Parser parser;

    return parser.ParseFile(path, global_object);
}

}  // namespace gui
