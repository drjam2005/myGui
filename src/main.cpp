#include <raylib.h>
#include <iostream>
#include <gui.h>

int main(){
	// window 
	SetTraceLogLevel(LOG_ERROR); 
	InitWindow(500, 500, "myGui");
	SetTargetFPS(60);

	myGui::Slider slider({100,100,300,10}, {-100,200}, 25);

	// loop
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

		slider.Update();
		slider.Render();

        EndDrawing();
    }
}


