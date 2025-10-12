#pragma once
#ifndef MYGUI_H
#define MYGUI_H
#include <raylib.h>

#include <string>
#include <functional>
#include <vector>

namespace myGui {
	class Widget {
		private:
		public:
			std::vector<Widget*> objects;
			Rectangle dimensions;
			Rectangle padding;

			Widget(Rectangle dimensions, Rectangle padding={0.f,0.f,0.f,0.f});
			void AddObject(void* object);
			virtual void changePosition(Vector2 position);
			virtual void changeDimensions(Rectangle dimensions);
			virtual void Update();
			virtual void Render();
			virtual Rectangle getDimensions();
	};

	class Button : public Widget {
		private:
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
}
#endif
