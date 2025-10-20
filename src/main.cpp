#include <raylib.h>
#include <gui.h>

int main(){
	SetTraceLogLevel(LOG_ERROR); 
	InitWindow(500, 500, "myGui");
	SetTargetFPS(60);

	myGui::Slider slider({100,100,50,10}, {-100,200}, 50);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

		slider.Update();
		slider.Render();

        EndDrawing();
    }
}


