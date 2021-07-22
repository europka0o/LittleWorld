#include "InterfBase.hpp"
#pragma once

//#ifndef _MINBAR_H_
//#define _MINBAR_H_



namespace __interface_companents {
#pragma	pack(push, 1)
	class min_bar : public BaseInerface {
		private:
			int max_br, min_br, curr_br; //Максимальное значение полосы, минимальное значение полосы, текущее значение полосы 
			RectangleShape* main; //Прямоугольник под объектом
			RectangleShape* bevel; //Полоса
		public:
			/// <summary>
			/// Конструктор
			/// </summary>
			/// <param name="x">Позиция по оси X</param>
			/// <param name="y">Позиция по оси Y</param>
			/// <param name="br_ma">Максимальное значение полосы</param>
			/// <param name="br_mi">Минимальное значение полосы</param>
			/// <param name="mcol">Цвет полосы</param>
			/// <param name="bcol">Цвет прямоугольника под полосой</param>
			/// <returns></returns>
			min_bar(int x, int y, int br_ma, int br_mi, const Color& mcol, const Color& bcol);
			~min_bar();
			/// <summary>
			/// Устанавливает позицию объекта по осям X, Y
			/// </summary>
			/// <param name="x">Позиция по оси X</param>
			/// <param name="y">Позиция по оси Y</param>
			/// <returns></returns>
			void __fastcall setPosition(int x, int y) noexcept override;
			/// <summary>
			/// Устанавливает позицию объекта по осям X, Y
			/// </summary>
			/// <param name="xy">Структура axes_i с координатами по осям X и Y</param>
			void setPosition(const axes_i& xy) noexcept override;
			/// <summary>
			/// Изменяет состояние полосы
			/// </summary>
			/// <param name="arg">Новое значение полосы</param>
			/// <returns></returns>
			void changeBar(int arg) noexcept;
			void render(RenderWindow& wd) noexcept override;
	};
#pragma	pack(pop)
}

//#endif