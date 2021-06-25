#include "Camera.hpp"
#include "TextBox.hpp"
#include "Button.hpp"
#include "Gradient.hpp"
#include "CheckBox.hpp"
#include "ComboBox.hpp"
#pragma once

//#ifndef _MENUSETTINGS_H_
//#define _MENUSETTINGS_H_



class menu_settings {
	private:
		axes_i pos;
		RectangleShape* main, * border, * blackout;
		__interface_companents::text_box* txMenuSettings;
		__interface_companents::gradient* grFirst, * grSecond;
	public:
		bool active, blackout_visible;
		__interface_companents::button* btBack, * btSave;
		__interface_companents::text_box* txVertS, * txFullS, * txScreen, * txSound, * txSoundV, * txAnisF;
		__interface_companents::check_box* cbVertS, * cbFullS, * cbSound;
		__interface_companents::combo_box* combScreen, * combSoundV, * combAnisF;
		menu_settings(configuration* cf, Camera* camera, const Font& font, const Color& maincl, const Color& bordercl);
		menu_settings(configuration* cf, const Font& font, const Color& maincl, const Color& bordercl);
		~menu_settings();
		void backSettings(configuration* cf);
		int saveSettings(configuration* cf);
		void render(RenderWindow& wd, Camera* camera) noexcept;
		void render(RenderWindow& wd) noexcept;
};

//#endif