#include <raylib.h>
#include <iostream>
#include <gui.h>

int main(){
	// window 
	InitWindow(500, 500, "myGui");
	SetTargetFPS(60);
	// objects 
    myGui::Button button(
        {                   
            .x = 10,      
            .y = 0.2f,
            .width = 100,
            .height = 50
        },
        (char*)"Click Me!",
        5.0f
    );
	button.SetClick([&]{std::cout << "hi.." << std::endl;;});

    myGui::Button button2(
        {                   
            .x = 10,      
            .y = 0.2f,
            .width = 120,
            .height = 50
        },
        (char*)"Click Me!",
        5.0f
    );
	button2.SetClick([&]{std::cout << "hello.." << std::endl;;});

	std::string str = "hii...";
    myGui::TextField textfield(
        {                   
            .x = 10,      
            .y = 0.2f,
            .width = 120,
            .height = 50
        },
        &str,
        5.0f
    );
	myGui::Widget widget({10, 10, 150, 400}, {10, 10, 10, 10});
	widget.AddObject(&button);
	widget.AddObject(&button2);
	widget.AddObject(&textfield);

	// loop
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

		widget.Render();
		widget.Update();
		if(textfield.checkEnter()){
			std::cout << "Message: " << str << std::endl;
			str.clear();
		}

        EndDrawing();
    }
}


