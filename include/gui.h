#pragma once
#include <raylib.h>
#include <string>
#include <functional>

namespace myGui {
	class Button {
		private:
			Rectangle dimensions;
			float round = 0.f;
			bool autoscale = false;
			char* text = nullptr;

			std::function<void()> onClick;
			std::function<void()> onHold;
			std::function<void()> onRelease;
		public:
			Button(){}
			Button(Rectangle, char*, float round=0.0f);
			void SetClick(std::function<void()>);
			void SetHold(std::function<void()>);
			void SetRelease(std::function<void()>);

			void Render();
			void Update();
	};

	class TextField {
		private:
			Rectangle dimensions;
			std::string* outputMessage;
			float round = 0.f;
		public:
			std::string currentMessage = "";
			bool isInText = false;
			TextField(){}
			TextField(Rectangle, std::string*, float round=0.0f);

			void Render();
			bool Update();
	};
}
