#include "ilpch.h"
#include "imgui_layer/parser/parser.h"

namespace gui
{

/* Parser */
ParserResult Parser::ParseFile(const std::string file, GlobalObject& dest)
{
    return ParserResult(ParserResultType::kFileNotFound);
}

}  // namespace gui
