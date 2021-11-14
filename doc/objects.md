# Objects
1. [GlobalObject](#GlobalObject)
2. [Panel](#Panel)
---
## GlobalObject
### Description:
The global object is automatically generated and used as the global scope of the file. It can be referenced by the object name "global". The attributes of the object are used to descripe the file. You cant create a global object manually.
### Attributes:
| Name        | Type   | Description                                                     | Default Value |
| ----------- | ------ | --------------------------------------------------------------- | ------------- |
| id          | String | The ID of the file, can be used to reference it in the backend. | ""            |
| version     | String | Version of the file                                             | ""            |
| description | String | Description of the file                                         | ""            |
| author      | String | Author of the file                                              | ""            |
| date        | String | Date when the file was changed                                  | ""            |
### Example:
```
# example.ill:

id          = "plugin_0"
version     = "1.2.3"
description = "Example file for the global object"
author      = "Max"
date        = "19.2.1980"

Panel
{
    title = "Panel_0"

    Text { text = global.id          }
    Text { text = global.version     }
    Text { text = global.description }
    Text { text = global.author      }
    Text { text = global.date        }
}
```
---
## Panel
### Description:
The panel is equal to ```ImGui::BeginWindow()``` and ```ImGui::EndWindow()```. It is necessary to draw other objects.
### Attributes:
| Name     | Type   | Description | Default Value |
| ---------| ------ | ------------| --------------|
| position | Vec2   | The start position of the panel relative to the window | (0, 0) |
| size     | Vec2   | The start size of the panel | Based on the size of the child objects. |
| title    | String | The title of the window wich is also used as the ImGui-ID, therefore it has to be unique and should be set, even if the panel has no titlebar. It can lead to unexpected behaviour when multiple panels have the same title. | If Object-ID is set, the Object-ID will be used as the title. If both title and Object-ID are not set, the title will be "unknown".
### Example:
```
# example.ill:

Panel
{
    title = "Example panel"
    pos   = (300, 300)
    size  = (550.5, 550.5)

    Text { text = "This is a text inside the panel" }
}

// Title is "Title by attribute"
Panel
{
    title = "Title by attribute"
}

// Title is "title_by_object_id"
Panel : title_by_object_id
{
}

// Title is "unknown"
Panel
{
}
```
