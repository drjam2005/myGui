#include <iostream>
#include <gui.h>

int main(void) {
	InitWindow(800, 600, "title");
	SetTargetFPS(60);

	myGui::Button button({0.5, 0.5, 0.25, 0.25}, "Click Me!", 2.0f);
	button.SetClick  ([&]{std::cout << "click"   << std::endl;});
	button.SetHold   ([&]{std::cout << "hold"    << std::endl;});
	button.SetRelease([&]{std::cout << "release" << std::endl;});

	std::string message = "yooo";
	myGui::TextField textField({5.0, 5.0, 200.0f, 75.0f}, &message, 5.0f);

	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);

		button.Update();
		button.Render();

		if(textField.Update()){
			std::cout << message << std::endl;
		}
		textField.Render();


		EndDrawing();
	}
    return 0;
}
