#include "InterfBase.hpp"
#include "Camera.hpp"
#pragma once

//#ifndef _BAR_H_
//#define _BAR_H_



namespace __interface_companents {
	class bar : public BaseInerface {
		private:
			int max_bar, min_bar, curr_bar; //Максимальное значение полосы, минимальное значение полосы, текущее значение полосы
			RectangleShape* main; //Прямоугольник под объектом
			RectangleShape* bevel; //Полоса
			Text* label;
		public:
			/// <summary>
			/// Конструктор
			/// </summary>
			/// <param name="x">Позиция по оси X</param>
			/// <param name="y">Позиция по оси Y</param>
			/// <param name="br_ma">Максимальное значение полосы</param>
			/// <param name="br_mi">Минимальное значение полосы</param>
			/// <param name="name">Текст перед полосой</param>
			/// <param name="mcol">Цвет полосы</param>
			/// <param name="bcol">Цвет прямоугольника под полосой</param>
			/// <param name="tcol">Цвет текста</param>
			/// <returns></returns>
			bar(const Font& font, int x = 0, int y = 0, int br_ma = 100, int br_mi = 0, const wchar_t* name = L"NON:", const Color& mcol = Color::White, const Color& bcol = Color::Red, const Color& tcol = Color::Black);
			bar(); //Конструктор по умолчанию
			~bar(); //Деструктор
			/// <summary>
			/// Изменяет состояние полосы
			/// </summary>
			/// <param name="arg">Новое значение полосы</param>
			/// <returns></returns>
			void __fastcall changeBar(int arg) noexcept;
			void render(RenderWindow& wd) noexcept override;
			/// <summary>
			/// Устанавливает новую позицию объекта 
			/// </summary>
			/// <param name="x">Позиция по оси X</param>
			/// <param name="y">Позиция по оси Y</param>
			/// <returns></returns>
			void __fastcall setPosition(int x, int y) noexcept override;
			/// <summary>
			/// Устанавливает новую позицию объекта
			/// </summary>
			/// <param name="xy">Структура axes_i с координатами по осям X и Y</param>
			void setPosition(const axes_i& xy) noexcept override;
			/// <summary>
			/// Изменяет размер текста
			/// </summary>
			/// <param name="size">Новый размер текста в пикселях</param>
			/// <returns></returns>
			void resize(int size = normal) noexcept;
			/// <summary>
			/// Замораживает позицию объекта относительно камеры
			/// </summary>
			/// <param name="camera">Указатель на камеру</param>
			/// <param name="xy">Структура с координатами заморозки</param>
			void freeze(Camera* camera, const axes_i& xy) noexcept;
			/// <summary>
			/// Замораживает позицию объекта относительно камеры
			/// </summary>
			/// <param name="camera">Указатель на камеру</param>
			/// <param name="x">Координаты по оси X</param>
			/// <param name="y">Координаты по оси Y</param>
			void freeze(Camera* camera, int x, int y) noexcept;
	};
}

//#endif