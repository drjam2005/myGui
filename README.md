 myGui
===
    - A raylib based, immediate mode GUI rendering utility for personal use and study
      still very much in a Work in Progress...

## Features
- Button
- TextField
- ~~Checkbox~~
- ~~Radio buttons~~
- ~~Slider~~

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

    button.SetClick  ([&]{ doX(5);});
 // button.SetHold   ([&]{ doX(5);6)});
 // button.SetRelease([&]{ doX(5);7)});

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
}
```

