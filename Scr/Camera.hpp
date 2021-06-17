#include "Base.hpp"
#pragma once

//#ifndef _CAMERA_H_ 
//#define _CAMERA_H_



class Camera {
	private:
		axes_i pos;
		int screen_H, screen_W; //Высота и ширана вьюпорта камеры
	public:
		/// <summary>
		/// Конструктор
		/// </summary>
		/// <param name="x">Позиция по оси X</param>
		/// <param name="y">Позиция по оси Y</param>
		/// <param name="screen_width">Ширина вьюпорта в пикселях</param>
		/// <param name="screen_height">Высота вьюпорта в пикселях</param>
		/// <returns></returns>
		Camera(int x, int y, int screen_width, int screen_height);
		Camera(); //Конструктор по умолчанию
		~Camera(); //Деструктор
		View* Vid;
		/// <summary>
		/// Перемещает камеру
		/// </summary>
		/// <param name="x">Новая позиция по оси X</param>
		/// <param name="y">Новая позиция по оси Y</param>
		void __fastcall move(int x, int y); //Передвигает камеру на новую позицию по осям X, Y
		/// <summary>
		/// Устанавливает зум камеры
		/// </summary>
		/// <param name="zoom">Прибавка к текущему зуму, зум по умолчанию равен 1</param>
		void setZoom(float zoom);
		/// <summary>
		/// Возвращает позицию камеры
		/// </summary>
		/// <returns>Структура axes_i</returns>
		const axes_i& getPosition() const noexcept;
		/// <summary>
		/// Возвращает ширину вьюпорта камеры в пикселях  
		/// </summary>
		/// <returns>Количество пикселей в int</returns>
		int getScreenWidth() const noexcept;
		/// <summary>
		/// Возвращает высоту вьюпорта камеры в пикселях 
		/// </summary>
		/// <returns>Количество пикселей в int</returns>
		int getScreenHeight() const noexcept;
		/// <summary>
		/// Возвращает данные о хитбоке: ширина, высота, функции проверки пересечения
		/// </summary>
		/// <returns>Структура FloatRect</returns>
		const FloatRect& getBounds() const noexcept;
		void setView(RenderWindow& wd);
};

//#endif