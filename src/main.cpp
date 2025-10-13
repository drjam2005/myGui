#include <raylib.h>
#include <iostream>
#include <gui.h>

int main(){
	// window 
	SetTraceLogLevel(LOG_ERROR); 
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
            .width = 200,
            .height = 50
        },
        &str,
        5.0f
    );
    myGui::Button button3(
        {                   
            .x = 10,      
            .y = 0.2f,
            .width = 120,
            .height = 50
        },
        (char*)"submit",
        5.0f
    );
	myGui::Checkbox check({
			.x = 100,
			.y = 100
		},
		1,
		"hi...");
	button3.SetClick([&]{textfield.submitText();});
	myGui::Widget widget({10, 10, 150, 400}, {10, 10, 10, 10});
	widget.AddObject(&textfield);
	widget.AddObject(&check);
	widget.AddObject(&button3);

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


