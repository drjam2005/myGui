 myGui
===
    - A raylib based, retained mode GUI rendering utility for personal use and study
      still very much in a Work in Progress...

## Objects
- Widget (to store objects)
- Button
- TextField
- Checkbox (kinda done)
- Slider
- ~~Radio buttons~~

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

    button.SetClick  ([&]{ doX(5); });
 // button.SetHold   ([&]{ doX(6); );});
 // button.SetRelease([&]{ doX(7); );});

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
    std::string message = "Placeholder"; // will be used to store the message when the user presses KEY_ENTER
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

        textField.Update();
		if(textField.isSubmit()){ // check wether the user submitted
			std::cout << "Message: " << message << std::endl;
		}

        textField.Render();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
```

3. `Slider`
```cpp
#include <raylib.h>
#include "gui.h"

int main(){
    // Slider initialization
    myGui::Slider slider(
            {
                .x = 20.0f,
                .y = 20.0f,
                .width = 200.0f, // optional, used to horizontally scale the slider
                .height = 0.0f // no implementation
            },
            {
                .x = -50, // min
                .y = 100 // max
            },
            25.0f // optional starting value
        );
    InitWindow(500, 500, "myGui");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        
        slider.Update();
        slider.Render();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
```

## Widget usage
    - You can use widgets to store multiple objects into one pane
```cpp
#include <raylib.h>
#include <string>
#include "gui.h"

int main(){
    // make sure to initialize the window first before calling widget
    InitWindow(500, 500, "myGui");
    SetTargetFPS(60);
    myGui::Widget widget(
        // title
        "myGui Widget",
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
