#include "Base.hpp"
#pragma once

//#ifndef _CAMERA_H_ 
//#define _CAMERA_H_



class Camera {
	private:
		axes_i pos;
		int screen_H, screen_W; //������ � ������ �������� ������
	public:
		/// <summary>
		/// �����������
		/// </summary>
		/// <param name="x">������� �� ��� X</param>
		/// <param name="y">������� �� ��� Y</param>
		/// <param name="screen_width">������ �������� � ��������</param>
		/// <param name="screen_height">������ �������� � ��������</param>
		/// <returns></returns>
		Camera(int x, int y, int screen_width, int screen_height);
		Camera(); //����������� �� ���������
		~Camera(); //����������
		View* Vid;
		/// <summary>
		/// ���������� ������
		/// </summary>
		/// <param name="x">����� ������� �� ��� X</param>
		/// <param name="y">����� ������� �� ��� Y</param>
		void __fastcall move(int x, int y); //����������� ������ �� ����� ������� �� ���� X, Y
		/// <summary>
		/// ������������� ��� ������
		/// </summary>
		/// <param name="zoom">�������� � �������� ����, ��� �� ��������� ����� 1</param>
		void setZoom(float zoom);
		/// <summary>
		/// ���������� ������� ������
		/// </summary>
		/// <returns>��������� axes_i</returns>
		const axes_i& getPosition() const noexcept;
		/// <summary>
		/// ���������� ������ �������� ������ � ��������  
		/// </summary>
		/// <returns>���������� �������� � int</returns>
		int getScreenWidth() const noexcept;
		/// <summary>
		/// ���������� ������ �������� ������ � �������� 
		/// </summary>
		/// <returns>���������� �������� � int</returns>
		int getScreenHeight() const noexcept;
		/// <summary>
		/// ���������� ������ � �������: ������, ������, ������� �������� �����������
		/// </summary>
		/// <returns>��������� FloatRect</returns>
		const FloatRect& getBounds() const noexcept;
		void setView(RenderWindow& wd);
};

//#endif