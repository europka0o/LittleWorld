#include "Base.hpp"
#pragma once

//#ifndef _TRIGGER_H_ 
//#define _TRIGGER_H_



class CollisionBox {
	private:
		axes_i pos;
		IntRect rect_collis;
	public:
		bool active;
		/// <summary>
		/// Конструктор
		/// </summary>
		/// <param name="rect">Хитбокс</param>
		/// <returns></returns>
		CollisionBox(const IntRect& rect);
		~CollisionBox();
		/// <summary>
		/// Устанавливает позицию хитбокса по осям X и Y
		/// </summary>
		/// <param name="x">Ось X</param>
		/// <param name="y">Ось Y</param>
		void __fastcall setPosition(int x, int y);
		/// <summary>
		/// Устанавливает позицию хитбокса по осям X и Y
		/// </summary>
		/// <param name="xy">Структура axes_i с координатами по осям X и Y</param>
		void setPosition(const axes_i& xy);
		/// <summary>
		/// Возвращает позицию хитбокса по осям X и Y
		/// </summary>
		/// <returns>Структура axes_i</returns>
		const axes_i& getPosition() const noexcept;
		/// <summary>
		/// Возвращает данные о хитбоке: ширина, высота, функции проверки пересечения
		/// </summary>
		/// <returns>Структура IntRect</returns>
		const IntRect& getBounds() const noexcept;
		/// <summary>
		/// Устанавливает новые данные о хитбоксе
		/// </summary>
		/// <param name="rect">Струткура IntRect с новыми параметрами</param>
		void setBounds(const IntRect& rect);
};

typedef CollisionBox Trigger;

//#endif