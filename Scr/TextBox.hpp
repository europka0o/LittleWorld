#include "InterfBase.hpp"
#include "Camera.hpp"
#pragma once

//#ifndef _TEXTBOX_H_
//#define _TEXTBOX_H_



namespace __interface_companents {
	class text_box : public BaseInerface {
		private:
			RectangleShape* bevel; //Прямоугольник под текстом 
		public:
			bool visible_bevel; //Видимость прямоугольника под текстом 
			Text* label;
			text_box(const Font& font, int x = 0, int y = 0, const wchar_t* txt = L"NON:", const Color& lbcol = Color::White, const Color& bvcol = Color::Black);
			~text_box();
			void setString(const wchar_t* txt) noexcept; //Задает текст 
			void setFont(const Font& font) noexcept; //Путь к фону для текста
			void __fastcall setPosition(int x, int y) noexcept override; //Устанавливает позицию объекта по осям X, Y
			void setPosition(const axes_i& xy) noexcept override; //Устанавливает позицию объекта по осям X, Y 
			void resize(int size = __interface_companents::text_size::normal) noexcept; //Задает размер объекта в пикселях
			void freeze(Camera* camera, const axes_i& xy); //Замораживает позицию компонента относительно камеры
			void freeze(Camera* camera, int x, int y); //Замораживает позицию компонента относительно камеры
			void render(RenderWindow& wd) noexcept override;
	};
}

//#endif