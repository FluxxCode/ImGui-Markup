#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_PARSER_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_PARSER_H_

#include <string>

#include "imgui_layer/objects/global_object.h"

namespace gui
{

enum class ParserResultType
{
    kSuccess,
    kFileNotFound,
    kUnableToOpenFile
};

class ParserResult
{
public:
    ParserResult(ParserResultType type);

    ParserResultType type_;

    bool operator==(const ParserResultType& right);
};

class Parser
{
public:
    /**
     * Parses the data from a file, containing the layer's markup language.
     * If the file does not exist or the parser is unable to open the file,
     * the parser will stop the process and return with an parser error result.
     *
     * @param file - Path to the file from where the data will be loaded.
     *               Absolute and relative paths are allowed.
     * @param dest - Reference to a GlobalObject receiving the generated
     *               object tree.
     * @return Result of the operation as a ParserResult, containing error type,
     *         message and line positions. If there was no error,
     *         the ParesrResultType will be set to ParserErrorType::kSuccess and
     *         the line positions are 0. Everything else is an error that
     *         occured while loading the file. This can contain an error from
     *         the Lexer, Parser and Interpreter. The parser will stop the
     *         process and the global_object will be empty when an error occured
     *         while parsing the file.
     */
    ParserResult ParseFile(const std::string file, GlobalObject& dest);

    /**
     * Parses raw string, containing the layer's markup language.
     *
     * @param data - String containg the layer's markup language.
     * @param dest - Reference to a GlobalObject receiving the generated
     *               object tree.
     * @return Result of the operation as a ParserResult, containing error type,
     *         message and line positions. If there was no error,
     *         the ParesrResultType will be set to ParserErrorType::kSuccess and
     *         the line positions are 0. Everything else is an error that
     *         occured while loading the file. This can contain an error from
     *         the Lexer, Parser and Interpreter. The parser will stop the
     *         process and the global_object will be empty when an error occured
     *         while parsing the file.
     */
    // NOTE: This function will be implemented later.
    //       Currently the focus is to be able to parse the data from a file.
    // ParserResult ParseData(const std::string data, GlobalObject& dest);
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_PARSER_H_
