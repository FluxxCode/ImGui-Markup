# imgui_layer
Object oriented layer above [ImGui](https://github.com/ocornut/imgui) with a simple markup language. The aim is to make it easier for users of software using ImGui to change or develop the GUI without having to recompile the project. <br/>
"imgui_layer" is a temporary name until I find a suitable one. Feel free to share your ideas :)
# Compile
## Windows
...
## Linux
...
# Examples
```cpp
// panel.ill
Panel
{
  Button : button_0
  {
    text = "Example button"
  }
  
  Text { text = "Some text" }
  
  Text : text_0
  {
    text = "Colored text"
    color = (0.3, 0.4, 0.6, 1.0)
  }
  
  Text
  {
    text = "Colored text"
    color = text_0.color
  }
}
```
```cpp
// main.cpp
gui::GlobalObject file;

void Init()
{
  if (!gui::FileManager::LoadFromFile("panel.ill", file))
    std::cerr << "Unable to load file: " << gui::FileManager::GetLastError().ToString() << std::endl;
}

void Update()
{
  file.Update();
  
  if (file.IsPressed("button_0"))
    std::cout << "Button is pressed" << std::endl;
}
```
...
# TODOs
- Linux support
- Parser system rework
- Implement every missing ImGui feature
- Global style
- Global file to allow panels to be aligned 

# Ideas
- Custom language files
- Ability to create variables, maybe with a container object
- Lua support
