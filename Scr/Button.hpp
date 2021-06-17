#include "InterfBase.hpp"
#include "Camera.hpp"
#pragma once

//#ifndef _BUTTON_H_
//#define _BUTTON_H_



namespace __interface_companents {
	class button : public BaseInerface {
		private:
			Text* txt;
			RectangleShape* main, * active_bvl;
		public:
			bool active;
			button(int x, int y, const Font& font, const wchar_t* text_box, const Color& maincl, const Color& textcl, const Color& activecl);
			~button();
			void setPosition(const axes_i& xy) override;
			void __fastcall setPosition(int x, int y) override;
			void render(RenderWindow& wd) noexcept override;
			void resize(int size);
			void freeze(Camera* camera, const axes_i& xy) noexcept; //Замораживает позицию компонента относительно камеры
			void freeze(Camera* camera, int x, int y) noexcept; //Замораживает позицию компонента относительно камеры
			bool __fastcall isAction(int x, int y);
			bool isAction(const axes_i& xy);
	};
}

//#endif