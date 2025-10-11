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
            .y = 0.2f, // Note: you can use values between 0 and 1 to indicade percentages of screen
            .width = 100,
            .height = 50
        },
        "Click Me!",        // text to render
        5.0f                // optional rounding
    );

    button.SetClick  ([&]{ doX(5);});
 // button.SetHold   ([&]{ doX(6);});
 // button.SetRelease([&]{ doX(7);});

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


