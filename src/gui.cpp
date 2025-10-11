#include <gui.h>
#ifdef MYGUI_H

// TODO:
//    Checkbox
//    Radio buttons
//    Slider


// Button implementation
myGui::Button::Button(Rectangle dimensions, char* text, float round){
	this->dimensions = dimensions;
	if(0.0f < dimensions.x && dimensions.x < 1.0f){
		this->dimensions.x = dimensions.x * GetScreenWidth();
	}
	if(0.0f < dimensions.width && dimensions.width < 1.0f){
		this->dimensions.width = dimensions.width * GetScreenWidth();
	}
	if(0.0f < dimensions.y && dimensions.y < 1.0f){
		this->dimensions.y = dimensions.y * GetScreenHeight();
	}
	if(0.0f < dimensions.height && dimensions.height < 1.0f){
		this->dimensions.height = dimensions.height * GetScreenHeight();
	}
	this->text = text;
	this->round = round;
}

void myGui::Button::SetClick(std::function<void()> func){
	this->onClick = func;
}
void myGui::Button::SetHold(std::function<void()> func){
	this->onHold = func;
}
void myGui::Button::SetRelease(std::function<void()> func){
	this->onRelease = func;
}

void myGui::Button::Render() {
    bool isInside = CheckCollisionPointRec(GetMousePosition(), dimensions);
	Color clr = WHITE;
	if(isInside)
		clr = GRAY;
	if(isInside && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		clr = DARKGRAY;

    Rectangle verticalPart = {
        dimensions.x + round,
        dimensions.y,
        dimensions.width - (2 * round),
        dimensions.height
    };

    Rectangle horizontalPart = {
        dimensions.x,
        dimensions.y + round,
        dimensions.width,
        dimensions.height - (2 * round),
    };

    DrawCircle(dimensions.x + round,               dimensions.y + round,               round, clr);
    DrawCircle(dimensions.x + dimensions.width - round, dimensions.y + round,               round, clr);
    DrawCircle(dimensions.x + round,               dimensions.y + dimensions.height - round, round, clr);
    DrawCircle(dimensions.x + dimensions.width - round, dimensions.y + dimensions.height - round, round, clr);

    DrawRectangle(verticalPart.x, verticalPart.y, verticalPart.width, verticalPart.height, clr);
    DrawRectangle(horizontalPart.x, horizontalPart.y, horizontalPart.width, horizontalPart.height, clr);

    DrawText(this->text, dimensions.x + 10, dimensions.y + 10, 10, BLACK);
}

void myGui::Button::Update(){
	bool isInside = CheckCollisionPointRec(GetMousePosition(), dimensions);
	if(isInside){
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			if(onClick)
				onClick();
		}
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
			if(onHold)
				onHold();
		}
		if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
			if(onRelease)
				onRelease();
		}
	}
}

// TextField implementation
myGui::TextField::TextField(Rectangle dimensions, std::string* initialMessage, float round){
	this->dimensions = dimensions;
	if(0.0f < dimensions.x && dimensions.x < 1.0f){
		this->dimensions.x = dimensions.x * GetScreenWidth();
	}
	if(0.0f < dimensions.width && dimensions.width < 1.0f){
		this->dimensions.width = dimensions.width * GetScreenWidth();
	}
	if(0.0f < dimensions.y && dimensions.y < 1.0f){
		this->dimensions.y = dimensions.y * GetScreenHeight();
	}
	if(0.0f < dimensions.height && dimensions.height < 1.0f){
		this->dimensions.height = dimensions.height * GetScreenHeight();
	}

	this->currentMessage = *initialMessage;
	this->outputMessage = initialMessage;
}

void myGui::TextField::Render(){
    bool isInside = CheckCollisionPointRec(GetMousePosition(), dimensions);
	Color clr = WHITE;
	if(isInside)
		clr = GRAY;
	if(isInside && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		clr = DARKGRAY;

    Rectangle verticalPart = {
        dimensions.x + round,
        dimensions.y,
        dimensions.width - (2 * round),
        dimensions.height
    };

    Rectangle horizontalPart = {
        dimensions.x,
        dimensions.y + round,
        dimensions.width,
        dimensions.height - (2 * round),
    };

    DrawCircle(dimensions.x + round,               dimensions.y + round,               round, clr);
    DrawCircle(dimensions.x + dimensions.width - round, dimensions.y + round,               round, clr);
    DrawCircle(dimensions.x + round,               dimensions.y + dimensions.height - round, round, clr);
    DrawCircle(dimensions.x + dimensions.width - round, dimensions.y + dimensions.height - round, round, clr);

    DrawRectangle(verticalPart.x, verticalPart.y, verticalPart.width, verticalPart.height, clr);
    DrawRectangle(horizontalPart.x, horizontalPart.y, horizontalPart.width, horizontalPart.height, clr);

	DrawText(TextFormat("%s", this->currentMessage.c_str()), dimensions.x + 10, dimensions.y + 10, 10, BLACK);
}

bool myGui::TextField::Update() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        isInText = CheckCollisionPointRec(GetMousePosition(), dimensions);
    if (!isInText) return false;

	if (IsKeyPressed(KEY_ENTER)) {
		if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))){
			currentMessage += '\n';
		}else{
			currentMessage.clear();
			*outputMessage = currentMessage;
			return true;
		}
	}

    int key = GetCharPressed();
    while (key > 0) {
        if (key >= 32 && key <= 125){
            currentMessage += static_cast<char>(key);
			*outputMessage = currentMessage;
		}
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !currentMessage.empty()){
        currentMessage.pop_back();
		*outputMessage = currentMessage;
	}

	return false;
}

#endif
