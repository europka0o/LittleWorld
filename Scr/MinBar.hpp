#include "InterfBase.hpp"
#pragma once

//#ifndef _MINBAR_H_
//#define _MINBAR_H_



namespace __interface_companents {
	class min_bar : public BaseInerface {
		private:
			int max_br, min_br, curr_br; //������������ �������� ������, ����������� �������� ������, ������� �������� ������ 
			RectangleShape* main; //������������� ��� ��������
			RectangleShape* bevel; //������
		public:
			/// <summary>
			/// �����������
			/// </summary>
			/// <param name="x">������� �� ��� X</param>
			/// <param name="y">������� �� ��� Y</param>
			/// <param name="br_ma">������������ �������� ������</param>
			/// <param name="br_mi">����������� �������� ������</param>
			/// <param name="mcol">���� ������</param>
			/// <param name="bcol">���� �������������� ��� �������</param>
			/// <returns></returns>
			min_bar(int x, int y, int br_ma, int br_mi, const Color& mcol, const Color& bcol);
			~min_bar();
			/// <summary>
			/// ������������� ������� ������� �� ���� X, Y
			/// </summary>
			/// <param name="x">������� �� ��� X</param>
			/// <param name="y">������� �� ��� Y</param>
			/// <returns></returns>
			void __fastcall setPosition(int x, int y) noexcept override;
			/// <summary>
			/// ������������� ������� ������� �� ���� X, Y
			/// </summary>
			/// <param name="xy">��������� axes_i � ������������ �� ���� X � Y</param>
			void setPosition(const axes_i& xy) noexcept override;
			/// <summary>
			/// �������� ��������� ������
			/// </summary>
			/// <param name="arg">����� �������� ������</param>
			/// <returns></returns>
			void changeBar(int arg) noexcept;
			void render(RenderWindow& wd) noexcept override;
	};
}

//#endif