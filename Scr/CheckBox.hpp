#include "InterfBase.hpp"
#pragma once

//#ifndef _CHECKBOX_H_
//#define _CHECKBOX_H_



namespace __interface_companents {
#pragma	pack(push, 1)
	class check_box : public BaseInerface {
		private:
			RectangleShape* main, * border, * check;
		public:
			bool isCheck;
			check_box(int x, int y, const Color& maincl, const Color& bordercl, const Color& checkcl);
			~check_box();
			void setPosition(const axes_i& xy) override;
			void __fastcall setPosition(int x, int y) override;
			void render(RenderWindow& wd) noexcept override;
			void invers(bool operation);
			void invers();
	};
#pragma	pack(pop)
}

//#endif