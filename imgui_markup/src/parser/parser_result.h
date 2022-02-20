#ifndef IMGUI_MARKUP_SRC_PARSER_PARSER_RESULT_H_
#define IMGUI_MARKUP_SRC_PARSER_PARSER_RESULT_H_

#include <string>
#include <vector>

namespace imgui_markup::internal
{

struct ParserPosition
{
    ParserPosition(std::vector<std::string> file_stack, std::string line,
                  size_t line_number, size_t start, size_t end);

    std::vector<std::string> file_stack;
    std::string line;
    size_t line_number;

    /**
     * Start and end are relative to the line.
     */
    size_t start;
    size_t end;
};


enum class ParserResultType
{
    kSuccess,

    // Lexer errors:
    kFileNotFound,
    kUnableToOpenFile,
    kInvalidSymbol,
    kUnknownLexerInstruction,
    kWrongIncludeArgument,
    kIncludeFileDoesNotExists,
    kUnableToOpenIncludeFile,
    kFileIncludesItself,
    kUnexpectedEndOfString,
    kInvalidNumber,

    // Parser errors:
    kUnexpectedBlockEnd,
    kUndefinedTokenSequence,
    kUnexpectedEndOfFile,
    kObjectIDWrongValueType,
    kExpectedStartOfBlock,
    kExpectedEqualSymbol,
    kUnableToCreateObjectNode,
    kUnableToCreateAttributeAssignNode,
    kUnableToCreateStringNode,
    kUnableToCreateNumberNode,
    kUnableToCreateBoolNode,
    kUnableToCreateVectorNode,
    kUnableToCreateAttributeAccessNode,
    kValueNodeWrongType,
    kUnexpectedEndOfVector,
    kMissingVectorValue,

    // Interpreter errors:
    kExpectedObjectDeclaration,
    kWrongBaseNode,
    kUndefinedObjectType,
    kAttributeDoesNotExists,
    kMissingAttributeValue,
    kUnknownAttributeValueType,
    kAttributeConversionError,
    kObjectIDAlreadyDefined,
    kObjectIDGlobalIsReserved,
    kObjectIsNotDefined,
    kNoAttributeSpecified,
    kObjectIsNotValid,
    kInternalWrongNodeType
};

class ParserResult
{
public:
    ParserResult();
    ParserResult(ParserResultType type);
    ParserResult(ParserResultType type, std::string message,
                 ParserPosition position);

    ParserResultType type_;
    std::string message_;
    ParserPosition position_;

    std::string ToString() const;

    operator bool() const;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_PARSER_PARSER_RESULT_H_