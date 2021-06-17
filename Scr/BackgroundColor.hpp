#include "Base.hpp"
#pragma once

class background_color {
	private:
		axes_i pos;
		RectangleShape* background;
	public:
		bool visible;
		/// <summary>
		/// �����������
		/// </summary>
		/// <param name="x">������� �� ��� X</param>
		/// <param name="y">������� �� ��� Y</param>
		/// <param name="cl">����</param>
		/// <param name="cf">��������� �� ��������� ��������</param>
		background_color(int x, int y, const Color& cl, configuration* cf);
		~background_color();
		/// <summary>
		/// �������� ����
		/// </summary>
		/// <param name="cl">����� ����</param>
		void setColor(Color cl);
		void render(RenderWindow& wd) noexcept;
};