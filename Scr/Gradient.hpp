#include "InterfBase.hpp"
#pragma once

//#ifndef _GRADIENT_H_
//#define _GRADIENT_H_



namespace __interface_companents {
	class gradient : public BaseInerface {
		private:
			std::vector<sf::Color> colors;
			sf::VertexArray* rect;
		public:
			/// <param name="rt">������ � ��������� ��������</param>
			/// <param name="gd">����������� ���������</param>
			/// <param name="first">��������� ���� ���������</param>
			/// <param name="second">�������� ���� ���������</param>
			gradient(const FloatRect& rt, int gd, const Color& first, const Color& second);
			~gradient();
			/// <summary>
			/// ������������� ������� ������� �� ���� X � Y
			/// </summary>
			/// <param name="xy">��������� axes_i � ������������ �� ���� X � Y</param>
			void setPosition(const axes_i& xy) override;
			/// <summary>
			/// ������������� ������� ������� �� ���� X � Y
			/// </summary>
			/// <param name="x">���������� �� ��� X</param>
			/// <param name="x">���������� �� ��� Y</param>
			void __fastcall setPosition(int x, int y) override;
			void render(RenderWindow& wd) noexcept override;
	};
}

//#endif