 myGui
===
    - A raylib based, immediate mode GUI rendering utility for personal use and study
      still very much in a Work in Progress...

## Objects
- Widget (to store objects)
- Button
- TextField
- Checkbox (kinda done)
- ~~Radio buttons~~
- ~~Slider~~

# Usage

## For single standard use
1. `Button`
```cpp
#include <raylib.h>
#include "gui.h"

void doX(int x){
    // function x
}

int main(){
    // button initialization
    myGui::Button button(
        {                   // dimensions
            .x = 10,      
            .y = .2, // Note: you can use values between 0 and 1 to indicade percentages of screen
            .width = 100,
            .height = 50
        },
        "Click Me!",        // text to render
        5.0f                // optional rounding
    );

    button.SetClick  ([&]{ doX(5);});
 // button.SetHold   ([&]{ doX(6);)});
 // button.SetRelease([&]{ doX(7);)});

    InitWindow(500, 500, "myGui");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        button.Update();
        button.Render();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

```


2. `TextField`
```cpp
#include <iostream>
#include <raylib.h>
#include "gui.h"

int main(){
    // textfield initialization
    std::string message = ""; // will be used to store the message when the user presses KEY_ENTER
    myGui::TextField textField(
        {
            .x = 10,
            .y = .2, // Note: you can use values between 0 and 1 to indicade percentages of screen
            .width = 100,
            .height = 50
        },
        &message,
        5.0f
    );


    InitWindow(500, 500, "myGui");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

		std::cout << "Message: " << message << std::endl;
        if(textField.Update()) { // returns true if the user presses enter
			std::cout << "User pressed Enter!" << std::endl;
        }
        textField.Render();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
```

## Widget usage
    - You can use widgets to store multiple 
```cpp
#include <raylib.h>
#include <string>
#include "gui.h"

int main(){
    // make sure to initialize the window first before calling widget
    InitWindow(500, 500, "myGui");
    SetTargetFPS(60);
    myGui::Widget widget(
        // dimensions
        {
            .x = 10,
            .y = 10,
            .width = 100,
            .height = 250
        },
        // padding
        {
            .x = 10,
            .y = 10,
            .width = 10,
            .height = 10
    });

    myGui::Button button1({
        /* initial x and y values are ignored,
           as they are organized in the widget */
        { .x = 10.0f, .y = 10.0f, // <- ignored
          .width = 200 // <- width is capped at widget with - padding.x - padding.width
          .height = 100,
        }, 
        "hi...",
        2.0f
    });
    std::string text = "test";
    myGui::TextFieldl textfield({
        { .x = 10.0f, .y = 10.0f, // <- ignored
          .width = 200 
          .height = 100,
        },
        &text,
        2.0f
    });

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        
        widget.Update();
        widget.Render();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
```
