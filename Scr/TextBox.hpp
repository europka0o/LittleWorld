#include "InterfBase.hpp"
#include "Camera.hpp"
#pragma once

//#ifndef _TEXTBOX_H_
//#define _TEXTBOX_H_



namespace __interface_companents {
	class text_box : public BaseInerface {
		private:
			RectangleShape* bevel; //������������� ��� ������� 
		public:
			bool visible_bevel; //��������� �������������� ��� ������� 
			Text* label;
			text_box(const Font& font, int x = 0, int y = 0, const wchar_t* txt = L"NON:", const Color& lbcol = Color::White, const Color& bvcol = Color::Black);
			~text_box();
			void setString(const wchar_t* txt) noexcept; //������ ����� 
			void setFont(const Font& font) noexcept; //���� � ���� ��� ������
			void __fastcall setPosition(int x, int y) noexcept override; //������������� ������� ������� �� ���� X, Y
			void setPosition(const axes_i& xy) noexcept override; //������������� ������� ������� �� ���� X, Y 
			void resize(int size = __interface_companents::text_size::normal) noexcept; //������ ������ ������� � ��������
			void freeze(Camera* camera, const axes_i& xy); //������������ ������� ���������� ������������ ������
			void freeze(Camera* camera, int x, int y); //������������ ������� ���������� ������������ ������
			void render(RenderWindow& wd) noexcept override;
	};
}

//#endif