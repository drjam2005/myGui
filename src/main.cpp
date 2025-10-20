#include <raylib.h>
#include <gui.h>
#include <iostream>

int main(){
    std::string message = "woah"; // will be used to store the message when the user presses KEY_ENTER
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
		if(textField.isSubmit()){
			std::cout << "Message: " << message << std::endl;
		}

        textField.Render();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

