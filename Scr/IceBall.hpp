#include "BaseCharacter.hpp"
#include "MinBar.hpp"
#pragma once

//#ifndef _ICEBALL_H_
//#define _ICEBALL_H_



class IceBall : public BaseCharacter {
	private:
		__interface_companents::min_bar* HP;
	public:
		IceBall(const Sprite& ptr_sprite, float X_POS, float Y_POS, int hp, unsigned int descendant = ICEBALL_CLASS);
		virtual ~IceBall();
		void __fastcall setPosition(float x, float y) noexcept override;
		void setPosition(const axes_f& xy) noexcept override;
		void __fastcall update(float time) noexcept;
		bool isCooldown(float time) override;
		void render(RenderWindow& wd, Sprite* ptr_sprite) noexcept override;
};

//#endif