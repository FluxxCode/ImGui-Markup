#include "ilpch.h"
#include "imgui_layer/parser/parser.h"

namespace gui
{

/* ParserResult */
ParserResult::ParserResult(ParserResultType type)
    : type_(type)
{ }

bool ParserResult::operator==(const ParserResult& left,
                              const ParserResultType& right)
{
    if (left.type_ == right)
        return true;
    return false;
}

/* Parser */
Parser::ParseFile(const std::string file, GlobalObject& dest)
{

}

}  // namespace gui
