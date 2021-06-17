#include "Object.hpp"
#pragma once

//#ifndef _METEOR_H_
//#define _METEOR_H_



class Meteor : public ObjectAnimated {
	private:
		axes_f pos_meteor;
		Vector2f start_point, mouse_point;
		float current_len, full_len;
		void isReachedPoint(float time);
	public:
		bool cooldown, reached_point, is_sound_play;
		Meteor(const Sprite& ptr_sprite, float X, float Y);
		~Meteor();
		void __fastcall update(float time) override final;
		void render(RenderWindow& wd, Sprite* ptr_sprite, Sprite* ptr_sprite_meteor) noexcept;
};

//#endif