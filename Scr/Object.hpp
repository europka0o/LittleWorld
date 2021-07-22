#include "Base.hpp"
#include "Trigger.hpp"
#pragma once

//#ifndef _OBJECT_H_
//#define _OBJECT_H_


#pragma	pack(push, 1)
class ObjectStatic {
	protected:
		axes_i pos;
	public:
		//Sprite* sprt;
		CollisionBox* rect_collis;
		IntRect sprite_rect;
		bool visible;
		/// <summary>
		/// Конструктор
		/// </summary>
		/// <param name="i">Указатель на текстуру</param>
		/// <param name="X">Координаты по оси X</param>
		/// <param name="Y">Координаты по оси Y</param>
		/// <returns></returns>
		ObjectStatic(const Sprite& ptr_sprite, float X, float Y);
		~ObjectStatic();
		/// <summary>
		/// Возвращает позицию
		/// </summary>
		/// <returns>Структура axes_i</returns>
		virtual const axes_i& getPosition() const noexcept;
		/// <summary>
		/// Устанавливает позицию хитбокса по осям X и Y
		/// </summary>
		/// <param name="x">Ось X</param>
		/// <param name="y">Ось Y</param>
		virtual void __fastcall setPosition(int x, int y);
		/// <summary>
		/// Устанавливает позицию хитбокса по осям X и Y
		/// </summary>
		/// <param name="xy">Структура axes_i с координатами по осям X и Y</param>
		virtual void setPosition(const axes_i& xy);
		virtual void render(RenderWindow& wd, Sprite* ptr_sprite) noexcept;
};
#pragma	pack(pop)

#pragma	pack(push, 1)
class ObjectAnimated : public ObjectStatic {
	protected:
		float frame;
	public:
		bool end;
		/// <summary>
		/// Конструктор
		/// </summary>
		/// <param name="i">Указатель на текстуру</param>
		/// <param name="X">Координаты по оси X</param>
		/// <param name="Y">Координаты по оси Y</param>
		/// <returns></returns>
		ObjectAnimated(const Sprite& ptr_sprite, float X, float Y);
		~ObjectAnimated();
		/// <summary>
		/// Обновление объекта
		/// </summary>
		/// <param name="time">Время, чем больше значение переменной, тем быстрее происходит обновление</param>
		virtual void __fastcall update(float time) = 0;
};
#pragma	pack(pop)

//#endif