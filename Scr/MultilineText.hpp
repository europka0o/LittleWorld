#include "InterfBase.hpp"
#pragma once

//#ifndef _MULTILINETEXT_H_
//#define _MULTILINETEXT_H_



namespace __interface_companents {
	class multiline_text {
		private:
			int SIZE_MSTX, max_length; //����������� �������(���-�� ����� � ���), ������������ ����� ������ � ��������
			axes_f pos; //��������� axes_f � ������������ �� ���� X � Y
			RectangleShape* bevel; //������������� ��� �������  
			Font* font_main;
		public:
			using dyn_vector_text = std::vector<Text*>;
			dyn_vector_text mass_string;
			bool visible; //��������� �������
			bool visible_bevel; //��������� �������������� ��� �������
			Color* bevel_cl;
			Color* label_cl;
			/// <summary>
			/// �����������
			/// </summary>
			/// <param name="x">������� �� ��� X</param>
			/// <param name="y">������� �� ��� Y</param>
			/// <param name="lbcol">���� ������</param>
			/// <param name="bvcol">���� �������������� ��� �������</param>
			/// <returns></returns>
			multiline_text(float x = 0, float y = 0, const Color& lbcol = Color::White, const Color& bvcol = Color::Black);
			~multiline_text() noexcept;
			/// <summary>
			/// �������� ������ ������
			/// </summary>
			/// <param name="size">������ ������ � ��������</param>
			/// <returns></returns>
			void resize(int size = normal) noexcept;
			/// <summary>
			/// ���������� ����� ����� ������
			/// </summary>
			/// <param name="txt">����� �� ����� �����</param>
			/// <returns></returns>
			void add(const std::wstring& txt) noexcept;
			void render(RenderWindow& wd) noexcept;
	};
}

//#endif