#include "BaseCharacter.hpp"
#include "MinBar.hpp"
#pragma once

//#ifndef _SPEARMAN_H_
//#define _SPEARMAN_H_


#pragma	pack(push, 1)
class Spearman : public BaseCharacter {
	private:
		direcrion4 direction, last_direction;
		__interface_companents::min_bar* HP;
	public:
		Spearman(const Sprite& ptr_sprite, float X_POS, float Y_POS, int hp, unsigned int descendant = SPEARMAN_CLASS);
		~Spearman();
		void __fastcall setPosition(float x, float y) noexcept override;
		void setPosition(const axes_f& xy) noexcept override;
		void __fastcall move(float time, direcrion4 direct = direcrion4::non) noexcept override;
		void __fastcall attack(float time) override;
		bool isCooldown(float time) override;
		void render(RenderWindow& wd, Sprite* ptr_sprite) override;
};
#pragma	pack(pop)

//#endif