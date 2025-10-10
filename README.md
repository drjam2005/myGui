 myGui
===
    - An immediate mode GUI rendering utility for personal use and study
      still very much in a Work in Progress...

## Features
- Button
- TextField

## Usage

1. `Button`
```cpp
#include <raylib.h>
#include <gui.h>

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

    button.SetClick  ([&]{ doX(5)});
 // button.SetHold   ([&]{ doX(6)});
 // button.SetRelease([&]{ doX(7)});

    InitWindow(500, 500, "myGui");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        button.Update();
        button.Render();

        EndDrawing();
    }
}

```


2. `TextField`
```cpp
#include <iostream>
#include <raylib.h>
#include <gui.h>

int main(){
    // textfield initialization
    std::string message = "Message!!"; // will be used to store the message
                                       // will also be used to initially fill the text buffer
    myGui::TextField textField(
        {                     // dimensions
            .x = 10,
            .y = .2, // Note: you can use values between 0 and 1 to indicade percentages of screen
            .width = 100,
            .height = 50
        },
        &message,             // the message
        5.0f                  // optional rounding
    );

    InitWindow(500, 500, "myGui");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        if(textField.Update()){ // returns true if the user presses a valid character that can be stored in the message
            std::cout << message << std::endl;
        }
        textField.Render();

        EndDrawing();
    }
}

```
