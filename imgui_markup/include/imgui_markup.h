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

namespace igm
{

/**
 * Parses a file containing the valid markup language used for the layer.
 *
 * @param[in] path - The path to the file that will get parsed.
 *                   Absolute and relative paths are allowed.
 *
 * @return ID of the loaded file context.
 */
size_t ParseFile(const char* path, bool* result = nullptr);

/**
 * Deletes both file context and result of a specific context.
 */
void FreeContext(size_t context, bool* result = nullptr);

/**
 * Get the last result of a specific context.
 */
Result GetLastResult(size_t context, bool* result = nullptr);

/**
 * Updates a specific context and all it's items.
 * Should be called every frame for every context that should be rendered.
 * The function has to be called after ImGui::NewFrame is called.
 *
 * @param[in] id - ID of the context that should be updated.
 * @param[in] display_width - Display width used as the size of all root items.
 *                            Usually this should be the same as the size of
 *                            the current window.
 *                            ImGuiIO.DisplaySize.x is used if its set to 0.
 * @param[in] display_height - Display height used as the size of
 *                             all root items. Usually this should be the same
 *                             as the size of the current window.
 *                             ImGuiIO.DisplaySize.y is used if its set to 0.
 */
void Update(size_t id, size_t display_width = 0,  size_t display_height = 0,
            bool* result = nullptr);

bool IsPressed(size_t context, std::string item_id,
               MouseButton button = MouseButton::kLeft, bool* result = nullptr);

bool IsHovered(size_t context, std::string item_id, bool* resutl = nullptr);

bool IsToggled(size_t context, std::string item_id, bool* resutl = nullptr);

}  // namespace igm

#endif  // IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_H_
