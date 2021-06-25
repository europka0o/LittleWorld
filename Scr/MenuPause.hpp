#include "Camera.hpp"
#include "TextBox.hpp"
#include "Button.hpp"
#include "Gradient.hpp"
#pragma once

//#ifndef _MENUPAUSE_H_
//#define _MENUPAUSE_H_



class menu_pause {
	private:
		axes_i pos;
		RectangleShape* main, * border, * blackout;
		__interface_companents::text_box* txMenu;
		__interface_companents::gradient* grFirst, * grSecond;
	public:
		bool active, blackout_visible;
		__interface_companents::button* btExit, * btContinue, * btOptions;
		menu_pause(Camera* camera, const Font& font, const Color& maincl, const Color& bordercl);
		~menu_pause();
		void render(RenderWindow& wd, Camera* camera) noexcept;
};

//#endif