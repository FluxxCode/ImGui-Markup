#include "ilpch.h"
#include "utility/utility.h"

namespace gui::utils
{

bool StringToInt(std::string str, int* dest)
{
    try
    {
        *dest = std::stoi(str);
        return true;
    }
    catch (std::invalid_argument const& e)
    {
        return false;
    }
    catch (std::out_of_range const& e)
    {
        return false;
    }
    catch (std::exception const& e)
    {
        return false;
    }
}

bool StringToFloat(std::string str, float* dest)
{
    try
    {
        *dest = std::stof(str);
        return true;
    }
    catch (std::invalid_argument const& e)
    {
        return false;
    }
    catch (std::out_of_range const& e)
    {
        return false;
    }
    catch (std::exception const& e)
    {
        return false;
    }
}

bool StringToBool(std::string str, bool* dest)
{
    if (str == "true" || str == "True" || str == "1")
        *dest = true;
    else if (str == "false" || str == "False" || str == "0")
        *dest = false;
    else
        return false;

    return true;
}

std::string BoolToString(const bool b)
{
    return b ? "true" : "false";
}

std::vector<std::string> SplitString(std::string str, const char c)
{
    std::stringstream ss(str);
    std::string segment;
    std::vector<std::string> segments;

    // Get every segment and push it to the vector
    while (std::getline(ss, segment, c))
        segments.push_back(segment);

    return segments;
}

void Log(const std::string message)
{
#ifdef _DEBUG

    std::cout << message << std::endl;

#endif
}

}  // namespace gui::utils
