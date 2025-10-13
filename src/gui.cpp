#include <gui.h>
#include <iostream>
#include <helpers.h>
#ifdef MYGUI_H

// TODO:
//    Checkbox
//    Radio buttons
//    Slider

// Widget
myGui::Widget::Widget(char* title, Rectangle dimensions, Rectangle padding){
	this->title = title;
	this->dimensions = dimensions;
	this->padding = padding;
}
void myGui::Widget::changePosition(Vector2 position){
	this->dimensions.x = position.x;
	this->dimensions.y = position.y;
}

void myGui::Widget::changeDimensions(Rectangle dimensions){
	this->dimensions = dimensions;
}

void myGui::Widget::Render(){
	float currentHeight = 0.0f;
	Rectangle collapseHitBox = {this->dimensions.x+this->dimensions.width-20, this->dimensions.y, 20, 20};
	DrawRectangleRec({this->dimensions.x, this->dimensions.y, this->dimensions.width, 20}, Color{30,30,55,255});
	DrawRectangleRec(collapseHitBox, Color{20,20,30,255});
	DrawText(this->title, this->dimensions.x+5, this->dimensions.y+5, 10, WHITE);
	if(isCollapsed) return;
	DrawRectangleRec({this->dimensions.x, this->dimensions.y+20, this->dimensions.width, this->dimensions.height-20}, Color{50,50,100,255});
	for (auto& object : objects) {
		currentHeight += object->getDimensions().height;
		if(currentHeight >= this->getDimensions().height) return;
		object->Render();
	}
}

void myGui::Widget::AddObject(void* object){
	Widget* objectToAdd = (Widget*)object;

	float currHeight = 15.0f;
	for (auto& obj : objects) {
		currHeight += padding.y + obj->getDimensions().height + padding.height;
		if(obj == object) {
			break;
		}
	}
	
	objectToAdd->changePosition(Vector2{
		this->dimensions.x + padding.x,
		this->dimensions.y + currHeight + padding.y
	});

	objectToAdd->changeDimensions(Rectangle{
			objectToAdd->dimensions.x,
			objectToAdd->dimensions.y,
			std::min(objectToAdd->dimensions.width, this->dimensions.width - padding.x - padding.width),
			objectToAdd->dimensions.height
		});

	objects.push_back(objectToAdd);
}

void myGui::Widget::Update() {
	Rectangle hitbox = {this->dimensions.x, this->dimensions.y, this->dimensions.width-20, 20};
	Rectangle collapseHitBox = {this->dimensions.x+this->dimensions.width-20, this->dimensions.y, 20, 20};
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		if(CheckCollisionPointRec(GetMousePosition(), collapseHitBox)){
			isCollapsed = !isCollapsed;
			return;
		}
	}
	if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
		if(CheckCollisionPointRec(GetMousePosition(), hitbox)){
			Vector2 offset = {GetMousePosition().x-20, GetMousePosition().y-10};
			this->changePosition(offset);
			float currHeight = 15.0f;
			for (auto& obj : objects) {
				obj->changeDimensions(
					Rectangle{
						this->dimensions.x + padding.x,
						this->dimensions.y + currHeight + padding.y,
						std::min(obj->getDimensions().width, this->dimensions.width - padding.x - padding.width),
						obj->getDimensions().height
					}
				);
				currHeight += obj->getDimensions().height + padding.y + padding.height;
			}
		}
	}

	for(auto& object : objects){
		object->Update();
	}
}
Rectangle myGui::Widget::getDimensions(){
	return dimensions;
}
// Button implementation
myGui::Button::Button(): Widget({},{}) {}
myGui::Button::Button(Rectangle dimensions, char* text, float round): 
	Widget("",dimensions)
{
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

void myGui::Button::changePosition(Vector2 position){
	this->dimensions.x = position.x;
	this->dimensions.y = position.y;
}

Rectangle myGui::Button::getDimensions(){
	return this->dimensions;
}

void myGui::Button::changeDimensions(Rectangle dimensions){
	this->dimensions = dimensions;
}

// TextField implementation
myGui::TextField::TextField(): Widget({},{}) {}
myGui::TextField::TextField(Rectangle dimensions, std::string* initialMessage, float round):
	Widget("",dimensions)
{
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

	this->outputMessage = initialMessage;
}

void myGui::TextField::Render(){
	Color clr = GRAY;
	if(isInText)
		clr = WHITE;

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

	Font font = GetFontDefault();
	float fontSize = 10.0f;
	float spacing = 1.0f;
	float maxWidth = dimensions.width - padding.x - padding.width - 30.0f;

	std::string wrappedText = WrapText(*outputMessage, maxWidth, fontSize, spacing, font);

	DrawTextEx(font, wrappedText.c_str(), {dimensions.x + 10, dimensions.y + 10}, fontSize, spacing, BLACK);

}

void myGui::TextField::Update() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        isInText = CheckCollisionPointRec(GetMousePosition(), dimensions);
    if (!isInText) return;

	if (IsKeyPressed(KEY_ENTER)) {
		if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))){
			*outputMessage += '\n';
		}else{
			isEnter = true;
			shouldClear = true;
			return;
		}
	}

    int key = GetCharPressed();
    while (key > 0) {
        if (key >= 32 && key <= 125){
            *outputMessage += static_cast<char>(key);
		}
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !outputMessage->empty()){
		outputMessage->pop_back();
	}

	if (shouldClear && !isEnter) {
        outputMessage->clear();
        shouldClear = false;
    }

	return;
}

bool myGui::TextField::checkEnter(){
	if(isEnter){
		isEnter = false;
		return true;
	}
	return false;
}
void myGui::TextField::changePosition(Vector2 position){
	this->dimensions.x = position.x;
	this->dimensions.y = position.y;
}

void myGui::TextField::submitText(){
	isEnter = true;
	shouldClear = true;
}

Rectangle myGui::TextField::getDimensions(){
	return this->dimensions;
}

void myGui::TextField::changeDimensions(Rectangle dimensions){
	this->dimensions = dimensions;
}

// Checkbox implementation
myGui::Checkbox::Checkbox(Vector2 position, int ID, char* text)
    : myGui::Widget("",{position.x, position.y, 20, 20})
{
	this->text = text;
    this->ID = ID;
    this->state = false;
}


void myGui::Checkbox::Render() {
	DrawRectangleRec(dimensions, WHITE);
	DrawText(this->text, dimensions.x + 30, dimensions.y + 5, 15, WHITE);
    if (state)
		DrawRectangleRec({
			dimensions.x + 5,
			dimensions.y + 5,
			dimensions.width - 10,
			dimensions.height - 10
		}, BLUE);
}


void myGui::Checkbox::Update() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), dimensions))
            state = !state;
	}
}



void myGui::Checkbox::changePosition(Vector2 givenPosition) {
    this->dimensions.x = givenPosition.x;
    this->dimensions.y = givenPosition.y;
}


void myGui::Checkbox::changeDimensions(Rectangle rect) {
    this->dimensions = rect;
}


Rectangle myGui::Checkbox::getDimensions() {
    return this->dimensions;
}

// Radio Button Implementation
#endif
