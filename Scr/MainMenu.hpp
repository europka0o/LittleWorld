#include "Camera.hpp"
#include "TextBox.hpp"
#include "Button.hpp"
#include "Gradient.hpp"
#pragma once

//#ifndef _MAINMENU_H_
//#define _MAINMENU_H_



class main_menu {
	private:
		RectangleShape* main;
		__interface_companents::text_box* txMainMenu;
		__interface_companents::gradient* grFirst, * grSecond;
	public:
		__interface_companents::button* btExit, * btStart, * btOptions, * btStartTren;
		main_menu(configuration* cf, const Font& font, const Color& maincl);
		~main_menu();
		void render(RenderWindow& wd) noexcept;
};

//#endif