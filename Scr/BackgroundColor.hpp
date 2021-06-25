#include "Base.hpp"
#pragma once

class background_color {
	private:
		axes_i pos;
		RectangleShape* background;
	public:
		bool visible;
		/// <summary>
		/// Конструктор
		/// </summary>
		/// <param name="x">Позиция по оси X</param>
		/// <param name="y">Позиция по оси Y</param>
		/// <param name="cl">Цвет</param>
		/// <param name="cf">Указатель на структуру настроек</param>
		background_color(int x, int y, const Color& cl, configuration* cf);
		~background_color();
		/// <summary>
		/// Изменяет цвет
		/// </summary>
		/// <param name="cl">Новый Цвет</param>
		void setColor(const Color &cl);
		void render(RenderWindow& wd) noexcept;
};