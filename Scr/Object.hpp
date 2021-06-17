#include "Base.hpp"
#include "Trigger.hpp"
#pragma once

//#ifndef _OBJECT_H_
//#define _OBJECT_H_



class ObjectStatic {
	protected:
		axes_i pos;
	public:
		//Sprite* sprt;
		CollisionBox* rect_collis;
		IntRect sprite_rect;
		bool visible;
		/// <summary>
		/// �����������
		/// </summary>
		/// <param name="i">��������� �� ��������</param>
		/// <param name="X">���������� �� ��� X</param>
		/// <param name="Y">���������� �� ��� Y</param>
		/// <returns></returns>
		ObjectStatic(const Sprite& ptr_sprite, float X, float Y);
		~ObjectStatic();
		/// <summary>
		/// ���������� �������
		/// </summary>
		/// <returns>��������� axes_i</returns>
		virtual const axes_i& getPosition() const noexcept;
		/// <summary>
		/// ������������� ������� �������� �� ���� X � Y
		/// </summary>
		/// <param name="x">��� X</param>
		/// <param name="y">��� Y</param>
		virtual void __fastcall setPosition(int x, int y);
		/// <summary>
		/// ������������� ������� �������� �� ���� X � Y
		/// </summary>
		/// <param name="xy">��������� axes_i � ������������ �� ���� X � Y</param>
		virtual void setPosition(const axes_i& xy);
		virtual void render(RenderWindow& wd, Sprite* ptr_sprite) noexcept;
};

class ObjectAnimated : public ObjectStatic {
	protected:
		float frame;
	public:
		bool end;
		/// <summary>
		/// �����������
		/// </summary>
		/// <param name="i">��������� �� ��������</param>
		/// <param name="X">���������� �� ��� X</param>
		/// <param name="Y">���������� �� ��� Y</param>
		/// <returns></returns>
		ObjectAnimated(const Sprite& ptr_sprite, float X, float Y);
		~ObjectAnimated();
		/// <summary>
		/// ���������� �������
		/// </summary>
		/// <param name="time">�����, ��� ������ �������� ����������, ��� ������� ���������� ����������</param>
		virtual void __fastcall update(float time);
};

//#endif