#ifndef IMGUI_MARKUP_SRC_PARSER_PARSER_RESULT_H_
#define IMGUI_MARKUP_SRC_PARSER_PARSER_RESULT_H_

#include <string>
#include <vector>

namespace igm::internal
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
    kExpectedAttributeID,
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
    kItemIDWrongValueType,
    kExpectedStartOfBlock,
    kExpectedEqualSymbol,
    kUnableToCreateItemNode,
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
    kExpectedItemDeclaration,
    kWrongBaseNode,
    kUndefinedItemType,
    kAttributeDoesNotExists,
    kMissingAttributeValue,
    kUnknownAttributeValueType,
    kAttributeConversionError,
    kItemIDAlreadyDefined,
    kItemIDGlobalIsReserved,
    kItemIsNotDefined,
    kNoAttributeSpecified,
    kItemIsNotValid,
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

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_PARSER_PARSER_RESULT_H_
