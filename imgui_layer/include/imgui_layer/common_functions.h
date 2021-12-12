#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_COMMON_FUNCTIONS_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_COMMON_FUNCTIONS_H_

#include "imgui_layer/parser/parser_error.h"
#include "imgui_layer/objects/global_object.h"

namespace gui
{

/**
 * Parses a file containing the valid markup language used for the layer.
 * The parser will create a GlobalObject, which is the root of
 * the loaded file containing every object that was specified.
 *
 * @param[in] path - The path to the file that will get loaded.
 *                   Absolute and relative paths are allowed.
 * @param[out] global_object - Reference to a buffer receiving the loaded data.
 *
 * @return Result of the operation as a ParserError, containing error type,
 *         message and line positions. If there was no error,
 *         the ParesrErrorType will be set to ParserErrorType::kSuccess and
 *         the line positions are 0. Everything else is an error that
 *         occured while loading the file. This can contain an error from the
 *         Lexer, Parser and Interpreter. The parser will stop the process
 *         and the global_object will be empty when an error occured while
 *         parsing the file.
 */
ParserError ParseFile(const char* path, GlobalObject& global_object);

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_COMMON_FUNCTIONS_H_
