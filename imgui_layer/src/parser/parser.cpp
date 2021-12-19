#include "ilpch.h"
#include "imgui_layer/parser/parser.h"

namespace gui
{

/* ParserResult */
ParserResult::ParserResult(ParserResultType type)
    : type_(type)
{ }

bool ParserResult::operator==(const ParserResultType& right)
{
    if (this->type_ == right)
        return true;
    return false;
}

/* Parser */
ParserResult Parser::ParseFile(const std::string file, GlobalObject& dest)
{

}

}  // namespace gui
