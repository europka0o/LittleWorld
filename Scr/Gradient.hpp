#include "InterfBase.hpp"
#pragma once

//#ifndef _GRADIENT_H_
//#define _GRADIENT_H_



namespace __interface_companents {
#pragma	pack(push, 1)
	class gradient : public BaseInerface {
		private:
			std::vector<sf::Color> colors;
			sf::VertexArray* rect;
		public:
			/// <param name="rt">Размер и положение хитбокса</param>
			/// <param name="gd">Направление градиента</param>
			/// <param name="first">Начальный цвет градиента</param>
			/// <param name="second">Конечный цвет градиента</param>
			gradient(const FloatRect& rt, int gd, const Color& first, const Color& second);
			~gradient();
			/// <summary>
			/// Устанавливает позицию объекта по осям X и Y
			/// </summary>
			/// <param name="xy">Структура axes_i с координатами по осям X и Y</param>
			void setPosition(const axes_i& xy) override;
			/// <summary>
			/// Устанавливает позицию объекта по осям X и Y
			/// </summary>
			/// <param name="x">Координаты по оси X</param>
			/// <param name="x">Координаты по оси Y</param>
			void __fastcall setPosition(int x, int y) override;
			void render(RenderWindow& wd) noexcept override;
	};
#pragma	pack(pop)
}

//#endif