#ifndef IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_H_
#define IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_H_

/**
 * @file imgui_markup.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Header used for applications using the imgui_layer
 * @copyright Copyright (c) 2021
 */

namespace imgui_markup
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
 * @return Result of the operation as a ParserResult, containing error type,
 *         message and line positions. If there was no error,
 *         the ParesrErrorType will be set to ParserErrorType::kSuccess and
 *         the line positions are 0. Everything else is an error that
 *         occured while loading the file. This can contain an error from the
 *         Lexer, Parser and Interpreter. The parser will stop the process
 *         and the global_object will be empty when an error occured while
 *         parsing the file.
 */
// ParserResult ParseFile(const char* path, GlobalObject& global_object);

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_H_
