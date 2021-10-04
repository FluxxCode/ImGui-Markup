#ifndef IMGUI_LAYER_SRC_PARSER_FILE_MANAGER_H_
#define IMGUI_LAYER_SRC_PARSER_FILE_MANAGER_H_

#include "objects/global_object.h"

namespace gui
{

class FileManager
{
public:
    // Constructors/Destructors
    FileManager(const FileManager&) = delete;

    // Operator
    void operator=(FileManager const&) = delete;

    // Functions
    static bool LoadFromFile(const std::string path, GlobalObject& dest);
    static bool LoadFromData(const std::string data, GlobalObject& dest);

private:
    // Constructor
    FileManager() { };

    // Functions
    static FileManager& Get();

    bool IMPLLoadFromFile(const std::string path, GlobalObject& dest);
    bool IMPLLoadFromData(const std::string data, GlobalObject& dest);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_PARSER_FILE_MANAGER_H_