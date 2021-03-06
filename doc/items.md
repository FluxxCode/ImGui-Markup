# Items
**Items:**
1. [Panel](#Panel)
    1. [PanelStyle](#PanelStyle)
1. [StackView](#StackView)
1. [Text](#Text)
1. [Button](#Button)
    1. [ButtonStyle](#ButtonStyle)
1. [Checkbox](#Checkbox)
1. [ChildPanel](#ChildPanel)

**Other:**
1. [Container](#Container)
1. [Attribute type items](#AttributeTypeItems)

---
## Panel
### Description:
The panel is equal to ```ImGui::BeginWindow()``` and ```ImGui::EndWindow()```.
Each drawable item must be created inside a panel.
### Attributes:
| Name | Type | Description | Default Value |
| --- | --- | --- | --- |
| position | Float2 | The start position of the panel, relative to the window. The attribute won't take effect if the panel is placed inside a view. | (0, 0) |
| size | Float2 | The start size of the panel. The attribute won't take effect if the panel is placed inside a view. | (0, 0) - Dynamic size based on the panel's child items. |
| title | String | The title of the panel | "##<item_address>", which is displayed as an empty string. |
| padding | Float2 | Padding to the panel's child items. | (0, 0) |
| no_title_bar | Bool | Disable title-bar | False |
| no_resize | Bool | Disable user resizing with the lower-right grip | False |
| no_move | Bool | Disable user moving the panel | False |
| no_collapse | Bool | Disable user collapsing panel by double-clicking on it. | False |
| always_auto_resize | Bool | Resize every panel to its content every frame. | False |
| no_background | Bool | Disable drawing background color and outside border. | False |
| no_mouse_inputs | Bool | Disable catching mouse, hovering test with pass through. | False |
| no_focus_on_appearing | Bool | Disable taking focus when transitioning from hidden to visible state. | False |
| no_bring_to_front_focus | Bool | Disable bringing panel to front when taking focus. | False |
| always_vertical_scrollbar | Bool | Always show vertical scrollbar. | False |
| always_horizontal_scrollbar | Bool | Always show horizontal scrollbar. | False |
| no_nav_inputs | Bool | No gamepad/keyboard navigation within the panel. | False |
| no_nav_focus | Bool | No focusing toward this panel with gamepad/keyboard navigation. | False |
| unsaved_document | Bool | Display a dot next to the title. | False |
| no_nav | Bool | Enables no_nav_inputs and no_nav_focus. | False |
| no_decoration | Bool | Enables no_title_bar, no_resize, no_scrollbar, no_collapse. | False |
| no_inputs | Bool | Enables no_mouse_inputs, no_nav_inputs, no_nav_focus. | False |
### Implemented API functions:
| Function | Description |
| --- | --- |
| ```bool IsItemPressed()``` | Returns true if the Panel is pressed by the user |
| ```bool IsItemHovered()``` | Returns true if the Panel is hovered by the user |
### Example:
```
// example.igm:

Panel
{
    title    = "Example panel"
    position = (300, 300)
    size     = (200, 200)

    Text { text = "This is a text inside the panel" }
}
```
![ExampleImage](img/items/panel.png)

---
## PanelStyle
### Description:
The panel style is used to change the appearance of a panel. Keep in mind that the PanelStyle can only be created inside a panel. The last defined PanelStyle is used if several are defined within a single panel.
### Attributes:
| Name | Type | Description | Default Value |
| --- | --- | --- | --- |
| background | Float4 | Panel background color | Global color is used |
| title_background | Float4 | Title background color | Global color is used |
| title_background_active | Float4 | Title background color when panel is active | Global color is used |
| title_background_collapsed | Float4 | Title background color when panel is collapsed | Global color is used |
| title_align | Float2 | Alignment of the panel title | Global alignment is used |
| scrollbar_background | Float4 | Scrollbar background color | Global color is used |
| scrollbar_grab | Float4 | Scrollbar grab color | Global color is used |
| scrollbar_grab_hovered | Float4 | Scrollbar grab color when hovered | Global color is used |
| scrollbar_grab_active | Float4 | Scrollbar grab color when pressed | Global color is used |
| rounding | Float2 | Rounding of the panel edges | Global rounding is used |
| border_size | Float2 | Size of the panel border. Value of 0 means no color. | Global border size is used |
| border_color | Float2 | Color of the border | Global border color is used |
```
// example.igm:

Panel
{
    title = "Example panel"
    size  = (200, 200)

    PanelStyle
    {
        background       = (0.2, 0.3, 0.4, 1.0)
        title_background = (0.4, 0.2, 0.6, 1.0)
        border_color     = (0.5, 0.4, 0.9, 1.0)
        border_size      = 1
    }
}
```
![ExampleImage](img/items/panel_style.png)

---
## StackView
### Description:
Stack views allow you to create automatic layouts by stacking its children's items on the desired axes.
While the items on the stacked axes only take up as much space as they need, they are stretched on the opposite axes to fill the entire area of the stack view.
The stack view can be placed within the global scope and any other item. Keep in mind that most of the drawable items won't update their child items, so placing the stack view inside most drawable item won't have any effect.
### Attributes:
| Name | Type | Description | Default Value |
| --- | --- | --- | --- |
| orientation | Enum\<Orientation> | Specifies the axes on which the items will be stacked | "Vertical" |
| padding | Float2 | Padding to the stack view's child items | Global item padding is used |
| item_spacing | Float | Spacing between the stack view's child items | Global item spacing is used |
```
// example.igm:

Panel
{
    title = "Example panel"

    StackView
    {
        padding = (10, 10)

        Text { text = "Hello world" }
        Text { text = "Hello world" }
        Text { text = "Hello world" }

        StackView
        {
            orientation = "Horizontal"
            padding = (10, 10)
            item_spacing = 5

            Button { text = "Hello world" }
            Button { text = "Hello world" }
            Button { text = "Hello world" }
        }

        Text { text = "Hello world" }
        Text { text = "Hello world" }
        Button { text = "Hello world" }
        Text { text = "Hello world" }
    }
}
```
![ExampleImage](img/items/stack_view.png)

---
## Text
### Description:
The text is equal to ```ImGui::Text()``` and is used to display information.
### Attributes:
| Name | Type | Description | Default Value |
| ---| --- | --- | --- |
| text | String | The Text that will be displayed | "##<item_address>", which is displayed as an empty string. |
| color | Float4 | The display color of the text | The global text color will be used |
### Implemented API functions:
| Function | Description |
| --- | --- |
| ```bool IsItemPressed()``` | Returns true if the Text is pressed by the user |
| ```bool IsItemHovered()``` | Returns true if the Text is hovered by the user |
### Example:
```
// example.igm:

Panel
{
    title    = "Example panel"
    position = (300, 300)
    size     = (250, 200)

    StackView
    {
        padding = (5, 5)

        Text
        {
            text = "Some information"
        }

        Text
        {
            text = "Colored text"
            color = (0.7, 0.2, 0.5, 1.0)
        }

        Text
        {
            text = "Colored text"
            color = (0.2, 0.8, 0.2, 1.0)
        }

        Text
        {
            text = "Colored text"
            color = (0.3, 0.5, 0.8, 1.0)
        }
    }
}
```
![ExampleImage](img/items/text.png)

---
## Button
### Description:
The button is equal to ```ImGui::Button()```.
### Attributes:
| Name | Type | Description | Default Value |
| --- | --- | --- | --- |
| text | String | The text that is displayed inside the button | "##<item_address>", which is displayed as an empty string. |
| size | Float2 | Size of the button | Size of the button contents |
### Implemented API functions:
| Function | Description |
| --- | --- |
| ```bool IsItemPressed()``` | Returns true if the button is pressed by the user |
| ```bool IsItemHovered()``` | Returns true if the button is hovered by the user |
### Example:
```
// example.igm:

Panel
{
    title    = "Example panel"
    position = (300, 300)
    size     = (220, 110)

    StackView
    {
        padding = (10, 10)

        Button : button_0
        {
            text = "Press me"
        }

        Button : button_1
        {
            text = "Press me"
        }
    }
}
```
```cpp
// example.cpp
if (gui::IsItemPressed(file, "button_0"))
    std::cout << "button_0 is pressed" << std::endl;

if (gui::IsItemHovered(file, "button_1"))
    std::cout << "button_1 is pressed" << std::endl;
```
![ExampleImage](img/items/button.png)

---
## ButtonStyle
### Description:
The button style is used to change the appearance of a button. Keep in mind that the ButtonStyle can only be created inside a button. The last defined ButtonStyle is used if several are defined within a single button.
### Attributes:
| Name | Type | Description | Default Value|
| --- | --- | --- | --- |
| color | Float4 | Default color of the button | Global button color is used |
| color_hovered | Float4 | Color of the button when it is hovered | Global button hovered color is used |
| color_active | Float4 | Color of the button when it is pressed | Global button active color is used |
| rounding | Float | Rounding of the button edges. Value between 0 and 12. | Global frame rounding is used |
| border_size | Float | Button border size. Value of 0 means no border. | Global frame border size is used |
| border_color | Float4 | Button border color | Global border color is used |
| border_shadow | Float4 | Border shadow color. Use an alpha value of 0 for no shadow. | Global border shadow color is used |
### Example:
```
// example.igm:

Panel
{
    title = "Example panel"
    size  = (130, 0)

    StackView
    {
        Button
        {
            text = "Green button"

            ButtonStyle
            {
                color         = (0.0, 1.0, 0.0, 1.0)
                color_hovered = (1.0, 0.0, 0.0, 1.0)
                color_active  = (0.0, 0.0, 1.0, 1.0)
                rounding      = 10
                border_size   = 1
                border_color  = (0.8, 0.3, 0.4, 1.0)
                border_shadow = (0.2, 0.2, 0.9, 0.5)
            }
        }
    }
}
```
![ExampleImage](img/items/button_style.png)

---
## Checkbox
### Description:
The checkbox is equal to ```ImGui::Checkbox()```.
### Attributes:
| Name | Type | Description | Default Value |
| ---| --- | --- | --- |
| text | String | Text that is displayed next to the checkbox | "##<item_address>", which is displayed as an empty string. |
| toggled | Bool | State of the checkbox when it's loaded | False |
### Implemented API functions:
| Function | Description |
| --- | --- |
| ```bool IsItemPressed()``` | Returns true if the checkbox or its text is pressed by the user. |
| ```bool IsItemHovered()``` | Returns true if the checkbox or its text is hovered by the user. |
| ```bool IsCheckboxToggled()``` | Returns the state of the checkbox. |
### Example:
```
// example.igm:

Panel
{
    title    = "Example panel"
    position = (300, 300)
    size     = (220, 110)

    StackView
    {
        Checkbox : checkbox_0
        {
            text = "Test checkbox 1"
            toggled = false
        }

        Checkbox : checkbox_1
        {
            text = "Test checkbox 2"
            toggled = true
        }
    }
}
```
```cpp
// example.cpp
if (gui::IsToggled(file, "checkbox_0"))
    std::cout << "checkbox_0 is toggled" << std::endl;

if (gui::IsToggled(file, "checkbox_1"))
    std::cout << "checkbox_1 is toggled" << std::endl;
```
![ExampleImage](img/items/checkbox.png)

---
## ChildPanel
### Description:
The ChildPanel is equal to ```ImGui::BeginChild()``` and ```ImGui::EndChild()```.
### Attributes:
| Name | Type | Description | Default Value |
| --- | --- | --- | --- |
| title | String | The title of the child panel. |  "##<item_address>", which is displayed as an empty string. |
| border | Bool | Sets if a border should be drawn around the child panel | False |
| padding | Float2 | Padding to the panel's child items. | (0, 0) |
### Implemented API functions:
| Function | Description |
| --- | --- |
| ```bool IsItemPressed()``` | Returns true if the ChildPanel is pressed by the user |
| ```bool IsItemHovered()``` | Returns true if the ChildPanel is hovered by the user |
### Example:
```
// example.igm:

Panel
{
    title    = "Example panel"
    position = (300, 300)
    size     = (250, 200)

    ChildPanel : child_panel
    {
        border = true
        size   = (220, 60)

        Text { text = "Text inside the child panel" color = (0.7, 0.2, 0.5, 1.0) }
        Text { text = "Text inside the child panel" color = (0.2, 0.8, 0.2, 1.0) }
        Text { text = "Text inside the child panel" color = (0.3, 0.5, 0.8, 1.0) }
        Text { text = "Text inside the child panel" color = (0.5, 0.2, 0.8, 1.0) }
    }
}
```
![ExampleImage](img/items/childpanel.png)

---
## Container
### Description:
The container is used to store custom data and can only be created in the global file scope.
### Attributes:
*The container currently does not have any attributes*
### Example:
```
// example.igm:

Container : colors
{
    Float4 : red   { value = (1.0, 0.0, 0.0, 1.0) }
    Float4 : green { value = (0.0, 1.0, 0.0, 1.0) }
    Float4 : blue  { value = (0.0, 0.0, 1.0, 1.0) }
}

Panel
{
    title = "Container example"

    StackView
    {
        Text { text = "Red text"   color = @colors.red.value   }
        Text { text = "Green text" color = @colors.green.value }
        Text { text = "Blue text"  color = @colors.blue.value  }
    }
}
```
![ExampleImage](img/items/container.png)

---
## Attribute type items <a name="AttributeTypeItems"></a>
### Description:
The attribute type items are used to dynamically create values from the markup language. They represent every attribute type that exists in the markup language. This is useful to for example define colors and their values.
### Attributes:
| Name | Description |
| --- | --- |
| value  | Attribute that stores the custom value |
### Example:
```
// example.igm

Bool   : bool    { value = true         }
Float  : float   { value = 1.234        }
Float2 : float_2 { value = (1, 2)       }
Float3 : float_3 { value = (1, 2, 3)    }
Float4 : float_4 { value = (1, 2, 3, 4) }
Int    : int     { value = 1234         }
String : string  { value = "String"     }

Panel
{
    title = "Example"

    StackView
    {
        Text { text = @bool.value    }
        Text { text = @float.value   }
        Text { text = @float_2.value }
        Text { text = @float_3.value }
        Text { text = @float_4.value }
        Text { text = @int.value     }
        Text { text = @string.value  }
    }
}

Container : colors
{
    Float4 : red   { value = (1.0, 0.0, 0.0, 1.0) }
    Float4 : green { value = (0.0, 1.0, 0.0, 1.0) }
    Float4 : blue  { value = (0.0, 0.0, 1.0, 1.0) }
}

Panel
{
    title = "Color example"
    size = (100, 100)

    StackView
    {
        Text { text = "Red"   color = @colors.red.value   }
        Text { text = "Green" color = @colors.green.value }
        Text { text = "Blue"  color = @colors.blue.value  }
    }
}
```
![ExampleImage](img/items/attribute_types.png)
![ExampleImage](img/items/container_colors.png)
