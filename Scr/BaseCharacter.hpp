#include "Trigger.hpp"
#pragma once

//#ifndef _BASE_CHARACTER_H_
//#define _BASE_CHARACTER_H_



#define DEFULT_CLASS 0
#define SPEARMAN_CLASS 1
#define DESTROERCASTLE_CLASS 2
#define KNIGHT_CLASS 3
#define ICEBALL_CLASS 4

enum class direcrion4 {
	non,
	right = 1,
	left,
	up,
	down
};

class BaseCharacter {
	protected:
		axes_f pos;
		IntRect sprite_rect;
		float frame, timer_cooldown;
		bool zeroing;
	public:
		BaseCharacter();
		BaseCharacter(const Sprite& ptr_sprite, float x, float y, int _hp, unsigned int descendant = DEFULT_CLASS);
		BaseCharacter(const Sprite& ptr_sprite, const axes_f& xy, int _hp, unsigned int descendant = DEFULT_CLASS);
		virtual ~BaseCharacter();
		CollisionBox* rect_collis;
		unsigned int descendant_class;
		bool cooldown, is_dead, visible;
		int health;
		virtual const axes_f& getPosition() const noexcept;
		virtual void __fastcall setPosition(float x, float y);
		virtual void __fastcall setPosition(const axes_f& xy);
		virtual void __fastcall move(float time, direcrion4 direct = direcrion4::non) noexcept;
		virtual void __fastcall attack(float time);
		virtual bool isCooldown(float time);
		virtual const IntRect& getSize() const noexcept;
		virtual void render(RenderWindow& wd, Sprite* ptr_sprite);
};

//#endif 
