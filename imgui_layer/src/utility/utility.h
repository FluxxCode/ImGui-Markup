#ifndef IMGUI_LAYER_SRC_UTILITY_UTILITY_H_
#define IMGUI_LAYER_SRC_UTILITY_UTILITY_H_

#include <string>
#include <vector>

namespace gui::utils
{

bool StringToInt(std::string str, int* dest);
bool StringToFloat(std::string str, float* dest);
bool StringToBool(std::string str, bool* dest);
std::string BoolToString(const bool b);

std::vector<std::string> SplitString(std::string, const char c);

}  // namespace utils

#endif  // IMGUI_LAYER_SRC_UTILITY_UTILITY_H_
