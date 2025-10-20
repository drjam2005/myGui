#pragma once
#ifndef MYGUI_H
#define MYGUI_H
#include <raylib.h>

#include <string>
#include <functional>
#include <vector>

enum WIDGET_TYPE {
	WIDGET,
	BUTTON,
	TEXT_FIELD,
	CHECKBOX,
	RADIO_BUTTON
};

namespace myGui {
	class Widget {
		private:
		public:
			WIDGET_TYPE type = WIDGET;
			std::vector<Widget*> objects;
			Rectangle dimensions;
			Rectangle padding;
			bool isCollapsed = false;
			char* title = nullptr;

			Widget(char* title, Rectangle dimensions, Rectangle padding={0.f,0.f,0.f,0.f});
			void AddObject(void* object);
			virtual void changePosition(Vector2 position);
			virtual void changeDimensions(Rectangle dimensions);
			virtual void Update();
			virtual void Render();
			virtual Rectangle getDimensions();
	};

	class Button : public Widget {
		private:
			WIDGET_TYPE type = BUTTON;
			float round = 0.f;
			bool autoscale = false;
			char* text = nullptr;

			std::function<void()> onClick;
			std::function<void()> onHold;
			std::function<void()> onRelease;
		public:
			Button();
			Button(Rectangle, char*, float round=0.0f);
			void SetClick(std::function<void()>);
			void SetHold(std::function<void()>);
			void SetRelease(std::function<void()>);

			void Render() override;
			void Update() override;
			void changePosition(Vector2 position) override;
			void changeDimensions(Rectangle dimensions) override;
			Rectangle getDimensions() override;
	};

	class TextField : public Widget{
		private:
			WIDGET_TYPE type = TEXT_FIELD;
			std::string* outputMessage;
			float round = 0.f;
			bool isEnter = false;
			bool shouldClear = false;
		public:
			bool isInText = false;
			TextField();
			TextField(Rectangle, std::string*, float round=0.0f);

			void submitText();
			bool checkEnter();

			void Render() override;
			void Update() override;
			void changePosition(Vector2 position) override;
			void changeDimensions(Rectangle dimensions) override;
			Rectangle getDimensions() override;
	};

	class Checkbox : public Widget {
		private:
			WIDGET_TYPE type = CHECKBOX;
			int ID;
			int state = 0;
			char* text = nullptr;
		public:
			Checkbox(Vector2 position, int ID, char* text);

			void Update() override;
			void Render() override;
			void changePosition(Vector2 position) override;
			void changeDimensions(Rectangle dimensions) override;
			Rectangle getDimensions() override;
	};

	class RadioButton : public Widget {
		// TODO
	};

	class Slider : public Widget {
		private:
			float min = -1.0f;
			float max = -1.0f;
			float current = min;
		public:
			Slider(Rectangle dimensions, Vector2 range, float startVal=-1.0f);
			void Update() override;
			void Render() override;
			void changePosition(Vector2 position) override;
			void changeDimensions(Rectangle dimensons) override;
			Rectangle getDimensions() override;
	};
}
#endif
