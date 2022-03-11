#ifndef IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_H_
#define IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_H_

/**
 * @file imgui_markup.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Header used for applications using the imgui_layer
 * @copyright Copyright (c) 2021
 */

#include "result.h"
#include "input.h"

namespace imgui_markup
{

/**
 * Parses a file containing the valid markup language used for the layer.
 *
 * @param[in] path - The path to the file that will get loaded.
 *                   Absolute and relative paths are allowed.
 *
 * @return ID of the loaded file context.
 */
size_t ParseFile(const char* path, bool* result = nullptr);

/**
 * Deletes both file context and result of a specific context.
 */
void FreeContext(const size_t context, bool* result = nullptr);

/**
 * Get the last result of a specific context.
 */
Result GetLastResult(const size_t context, bool* result = nullptr);

/**
 * Updates a specific context.
 * Should be called ervery frame for every context that should be rendered.
 */
void Update(const size_t id, bool* result = nullptr);

bool IsPressed(
    size_t context, std::string item_id,
    MouseButton button = MouseButton::kLeft, bool* result = nullptr);

bool IsHovered(size_t context, std::string item_id, bool* resutl = nullptr);

bool IsToggled(size_t context, std::string item_id, bool* resutl = nullptr);

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_H_
