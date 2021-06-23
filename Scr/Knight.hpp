#include "BaseCharacter.hpp"
#include "MinBar.hpp"
#pragma once

//#ifndef _KNIGHT_H_
//#define _KNIGHT_H_



class Knight : public BaseCharacter {
	private:
		direcrion4 direction, last_direction;
		__interface_companents::min_bar* HP;
	public:
		Knight(const Sprite& ptr_sprite, float X_POS, float Y_POS, int hp, unsigned int descendant = KNIGHT_CLASS);
		virtual ~Knight();
		void __fastcall setPosition(float x, float y) noexcept override;
		void setPosition(const axes_f& xy) noexcept override;
		void __fastcall move(float time, direcrion4 direct = direcrion4::non) noexcept override;
		void __fastcall attack(float time) override;
		bool isCooldown(float time) override;
		void render(RenderWindow& wd, Sprite* ptr_sprite) override;
};

//#endif