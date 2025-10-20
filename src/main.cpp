#include <raylib.h>
#include <gui.h>
#include <iostream>

int main(){
	myGui::Button button({10, 10, 200, 100}, "wow", 20.0f);
	button.SetClick([&] { std::cout << "click..." << std::endl; });
	button.SetHold([&] { std::cout << "hold..." << std::endl; });
	button.SetRelease([&] { std::cout << "release..." << std::endl; });

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

