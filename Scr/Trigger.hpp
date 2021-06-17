#include "Base.hpp"
#pragma once

//#ifndef _TRIGGER_H_ 
//#define _TRIGGER_H_



class CollisionBox {
	private:
		axes_i pos;
		IntRect rect_collis;
	public:
		bool active;
		/// <summary>
		/// �����������
		/// </summary>
		/// <param name="rect">�������</param>
		/// <returns></returns>
		CollisionBox(const IntRect& rect);
		~CollisionBox();
		/// <summary>
		/// ������������� ������� �������� �� ���� X � Y
		/// </summary>
		/// <param name="x">��� X</param>
		/// <param name="y">��� Y</param>
		void __fastcall setPosition(int x, int y);
		/// <summary>
		/// ������������� ������� �������� �� ���� X � Y
		/// </summary>
		/// <param name="xy">��������� axes_i � ������������ �� ���� X � Y</param>
		void setPosition(const axes_i& xy);
		/// <summary>
		/// ���������� ������� �������� �� ���� X � Y
		/// </summary>
		/// <returns>��������� axes_i</returns>
		const axes_i& getPosition() const noexcept;
		/// <summary>
		/// ���������� ������ � �������: ������, ������, ������� �������� �����������
		/// </summary>
		/// <returns>��������� IntRect</returns>
		const IntRect& getBounds() const noexcept;
		/// <summary>
		/// ������������� ����� ������ � ��������
		/// </summary>
		/// <param name="rect">��������� IntRect � ������ �����������</param>
		void setBounds(const IntRect& rect);
};

typedef CollisionBox Trigger;

//#endif