#include "impch.h"
#include "imgui_markup/common_functions.h"

#include "imgui_markup/parser/parser.h"

namespace imgui_markup
{

ParserResult ParseFile(const char* path, GlobalObject& global_object)
{
    internal::parser::Parser parser;

    return parser.ParseFile(path, global_object);
}

}  // namespace imgui_markup
