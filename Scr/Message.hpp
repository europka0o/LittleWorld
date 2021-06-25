#include "InterfBase.hpp"
#include "Camera.hpp"
#include "TextBox.hpp"
#include "Button.hpp"
#include "Gradient.hpp"
#pragma once

//#ifndef _MESSAGE_H_
//#define _MESSAGE_H_



namespace __interface_companents {
	class message {
		private:
			axes_i pos;
			RectangleShape* main, * border;
			text_box* txInfo, * txMess;
			gradient* grFirst, * grSecond;
		public:
			bool active;
			button* btOk;
			message(int x, int y, const Font& font, const wchar_t* txt, const Color& maincl, const Color& bordercl, const Color& textcl);
			~message();
			void render(RenderWindow& wd, Camera* camera) noexcept;
			void render(RenderWindow& wd) noexcept;
	};
}

//#endif