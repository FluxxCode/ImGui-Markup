#ifndef IMGUI_LAYER_SRC_UTILITY_UTILITY_H_
#define IMGUI_LAYER_SRC_UTILITY_UTILITY_H_

#include <string>
#include <vector>
#include <iostream>

namespace gui::internal::utils
{

/**
 * Convert a string to an interger.
 *
 * @param[in] str   - The string that will be converted.
 * @param[out] dest - A pointer to an integer that will recive the converted
 *                    string.
 *
 * @return true if there was no error, false if the string could not be
 *         converted to an interger.
*/
bool StringToInt(std::string str, int* dest);

/**
 * Convert a string to a float.
 *
 * @param[in] str   - The string that will be converted.
 * @param[out] dest - A pointer to a float that will recive the converted
 *                    string.
 *
 * @return true if there was no error, false if the string could not be
 *         converted to a float.
*/
bool StringToFloat(std::string str, float* dest);

/**
 * Convert a string to a bool. The possible string values are:
 * "True", "true", "False, "false", "1" or "0".
 *
 * @param[in] str   - The string that will be converted.
 * @param[out] dest - A pointer to a bool that will recive the converted
 *                    string.
 *
 * @return true if there was no error, false if the string could not be
 *         converted to a bool.
*/
bool StringToBool(std::string str, bool* dest);

/**
 * Convert a bool to a string.
 *
 * @param[in] b - The bool that will be converted to the string.
 *
 * @return the converted bool as a string.
*/
std::string BoolToString(const bool b);

/**
 * Split a string by a single character and return the segment in a vector.
 *
 * @param[in] str - The string that will be converted
 *                  and contains the character.
 * @param[in] c   - The character where the sting will be split.
 *
 * @return A vector of every segment.
*/
std::vector<std::string> SplitString(std::string str, const char c);

/**
 * std::filesystem::exists wrapper to handle exceptions.
 */
bool PathExists(const std::string path);

/**
 *
 * Logs a message to the console if _DEBUG is defined.
 *
 * @param[in] message - The message that will be logged.
 */
void Log(const std::string message);

}  // namespace gui::internal::utils

#endif  // IMGUI_LAYER_SRC_UTILITY_UTILITY_H_
