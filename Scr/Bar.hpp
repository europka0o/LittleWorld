#include "InterfBase.hpp"
#include "Camera.hpp"
#pragma once

//#ifndef _BAR_H_
//#define _BAR_H_



namespace __interface_companents {
	class bar : public BaseInerface {
		private:
			int max_bar, min_bar, curr_bar; //������������ �������� ������, ����������� �������� ������, ������� �������� ������
			RectangleShape* main; //������������� ��� ��������
			RectangleShape* bevel; //������
			Text* label;
		public:
			/// <summary>
			/// �����������
			/// </summary>
			/// <param name="x">������� �� ��� X</param>
			/// <param name="y">������� �� ��� Y</param>
			/// <param name="br_ma">������������ �������� ������</param>
			/// <param name="br_mi">����������� �������� ������</param>
			/// <param name="name">����� ����� �������</param>
			/// <param name="mcol">���� ������</param>
			/// <param name="bcol">���� �������������� ��� �������</param>
			/// <param name="tcol">���� ������</param>
			/// <returns></returns>
			bar(const Font& font, int x = 0, int y = 0, int br_ma = 100, int br_mi = 0, const wchar_t* name = L"NON:", const Color& mcol = Color::White, const Color& bcol = Color::Red, const Color& tcol = Color::Black);
			bar(); //����������� �� ���������
			~bar(); //����������
			/// <summary>
			/// �������� ��������� ������
			/// </summary>
			/// <param name="arg">����� �������� ������</param>
			/// <returns></returns>
			void __fastcall changeBar(int arg) noexcept;
			void render(RenderWindow& wd) noexcept override;
			/// <summary>
			/// ������������� ����� ������� ������� 
			/// </summary>
			/// <param name="x">������� �� ��� X</param>
			/// <param name="y">������� �� ��� Y</param>
			/// <returns></returns>
			void __fastcall setPosition(int x, int y) noexcept override;
			/// <summary>
			/// ������������� ����� ������� �������
			/// </summary>
			/// <param name="xy">��������� axes_i � ������������ �� ���� X � Y</param>
			void setPosition(const axes_i& xy) noexcept override;
			/// <summary>
			/// �������� ������ ������
			/// </summary>
			/// <param name="size">����� ������ ������ � ��������</param>
			/// <returns></returns>
			void resize(int size = normal) noexcept;
			/// <summary>
			/// ������������ ������� ������� ������������ ������
			/// </summary>
			/// <param name="camera">��������� �� ������</param>
			/// <param name="xy">��������� � ������������ ���������</param>
			void freeze(Camera* camera, const axes_i& xy) noexcept;
			/// <summary>
			/// ������������ ������� ������� ������������ ������
			/// </summary>
			/// <param name="camera">��������� �� ������</param>
			/// <param name="x">���������� �� ��� X</param>
			/// <param name="y">���������� �� ��� Y</param>
			void freeze(Camera* camera, int x, int y) noexcept;
	};
}

//#endif