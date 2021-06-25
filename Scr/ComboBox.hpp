#include "InterfBase.hpp"
#pragma once

//#ifndef _COMBOBOX_H_
//#define _COMBOBOX_H_



namespace __interface_companents {
	class combo_box : public BaseInerface {
		private:
			struct cell {
				cell(Text txt, int val);
				Text text_box;
				int value;
			};
			Font* font;
			RectangleShape* main;
			Color text_cl, main_cl;
			std::vector<cell*> mass_text;
			std::vector<cell*>::iterator it;
		public:
			bool visible_main, active;
			combo_box(int x, int y, const Color& maincl, const Color& textcl);
			~combo_box();
			void setPosition(const axes_i& xy) override;
			void __fastcall setPosition(int x, int y) override;
			void add(const wchar_t* st, int val);
			void next();
			void back();
			bool __fastcall isAction(int x, int y);
			bool isAction(const axes_i& xy);
			const std::wstring getText() const noexcept;
			int getValue() const noexcept;
			void render(RenderWindow& wd) noexcept override;
	};
}

//#endif