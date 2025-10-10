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
        if(textField.Update()){ // returns true if the user presses enter
			std::cout << "User pressed Enter!" << std::endl;
        }
        textField.Render();

        EndDrawing();
    }
}

