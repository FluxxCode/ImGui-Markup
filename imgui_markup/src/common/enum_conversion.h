#ifndef IMGUI_MARKUP_SRC_COMMON_ENUM_CONVERSION_H_
#define IMGUI_MARKUP_SRC_COMMON_ENUM_CONVERSION_H_

/**
 * @file enum_conversion.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains every enum and conversion functions that can be used
 *        within the markup language.
 * @copyright Copyright (c) 2021
 */

namespace imgui_markup::internal::enums
{

enum class Alignment : unsigned char
{
    kLeft,
    kCenter,
    kRight
};
std::string GetEnumName(Alignment);
bool ConvertEnum(std::string value, Alignment& out);
bool ConvertEnum(Alignment value, std::string& out);

}  // namespace imgui_markup::internal::enums

#endif  // IMGUI_MARKUP_SRC_COMMON_ENUM_CONVERSION_H_
