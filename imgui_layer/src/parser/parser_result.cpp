#include "ilpch.h"
#include "imgui_layer/parser/parser_result.h"

namespace gui
{

ParserResult::ParserResult()
{ }

ParserResult::ParserResult(ParserResultType type)
    : type_(type)
{ }

bool ParserResult::operator==(const ParserResultType& right)
{
    if (this->type_ == right)
        return true;
    return false;
}

}  // namespace gui
