#include "InterfBase.hpp"
#pragma once

//#ifndef _MULTILINETEXT_H_
//#define _MULTILINETEXT_H_



namespace __interface_companents {
	class multiline_text {
		private:
			int SIZE_MSTX, max_length; //Размерность массива(кол-во строк в нем), максимальная длина текста в пикселях
			axes_f pos; //Структура axes_f с координатами по осям X и Y
			RectangleShape* bevel; //Прямоугольник под текстом  
			Font* font_main;
		public:
			using dyn_vector_text = std::vector<Text*>;
			dyn_vector_text mass_string;
			bool visible; //Видимость объекта
			bool visible_bevel; //Видимость прямоугольника под текстом
			Color bevel_cl, label_cl;
			/// <summary>
			/// Конструктор
			/// </summary>
			/// <param name="x">Позиция по оси X</param>
			/// <param name="y">Позиция по оси Y</param>
			/// <param name="lbcol">Цвет текста</param>
			/// <param name="bvcol">Цвет прямоугольника под текстом</param>
			/// <returns></returns>
			multiline_text(float x = 0, float y = 0, const Color& lbcol = Color::White, const Color& bvcol = Color::Black);
			~multiline_text() noexcept;
			/// <summary>
			/// Изменяет размер текста
			/// </summary>
			/// <param name="size">Размер текста в пикселях</param>
			/// <returns></returns>
			void resize(int size = normal) noexcept;
			/// <summary>
			/// Добавление новой линии текста
			/// </summary>
			/// <param name="txt">Текст на новой линии</param>
			/// <returns></returns>
			void add(const std::wstring& txt) noexcept;
			void render(RenderWindow& wd) noexcept;
	};
}

//#endif