#include "ilpch.h"
#include "imgui_layer/parser/parser_result.h"

namespace gui
{

ParserResult::ParserResult()
{ }

ParserResult::ParserResult(ParserResultType type)
    : type_(type)
{ }

std::string ParserResult::ToString() const
{
    return ParserResult::ResultTypeToString(this->type_);
}

ParserResult::operator bool() const
{
    return this->type_ == ParserResultType::kSuccess ? true : false;
}

std::string ParserResult::ResultTypeToString(const ParserResultType type)
{
    switch (type)
    {
    case ParserResultType::kSuccess:
        return "Sucess";
    case ParserResultType::kFileNotFound:
        return "File not found";
    case ParserResultType::kUnableToOpenFile:
        return "Unable to open file";
    case ParserResultType::kInvalidSymbol:
        return "Invalid symbol";
    case ParserResultType::kUnknownLexerInstruction:
        return "Unknown lexer instruction";
    case ParserResultType::kWrongIncludeArgument:
        return "Expecting string after include instruction";
    case ParserResultType::kIncludeFileDoesNotExists:
        return "Include file does not exists";
    case ParserResultType::kUnableToOpenIncludeFile:
        return "Unable to open include file";
    case ParserResultType::kFileIncludesItself:
        return "File includes itself";
    case ParserResultType::kUnexpectedEndOfString:
        return "Unexpected end of string";
    case ParserResultType::kInvalidNumber:
        return "Invalid number";

    default:
        return "Unknown error";
    }

    return "Unknown error";
}

}  // namespace gui
