#include "Meteor.hpp"

//--------------------------------------Метеорит-Meteor-Начало------------------------------------
Meteor::Meteor(const Sprite &ptr_sprite, float X, float Y) :
	cooldown(false),
	reached_point(false),
	is_sound_play(false),
	current_len(0),
	ObjectAnimated(ptr_sprite, X, Y) {
	sprite_rect = IntRect(400, 0, 400, 400); 
	rect_collis->setBounds(IntRect(0, 0, 1, 1));

	mouse_point.x = X + 200;
	mouse_point.y = Y + 200;

	start_point.x = mouse_point.x - 270;
	start_point.y = mouse_point.y - 1440;

	full_len = sqrt(pow(mouse_point.x - start_point.x, 2) + pow(mouse_point.y - start_point.y, 2));
}

Meteor::~Meteor() {}

void __fastcall Meteor::update(float time) {

	isReachedPoint(time);

	if (reached_point) {
		frame += 0.022 * time;
		if (frame > 24) {
			end = true;
		}

		if (frame >= 0 && frame <= 5) {
			sprite_rect = IntRect(400 * int(frame), 0, 400, 400); 
		} else if (frame >= 6 && frame <= 11) {
			sprite_rect = IntRect(400 * (int(frame) - 6), 400, 400, 400);
		} else if (frame >= 12 && frame <= 17) {
			sprite_rect = IntRect(400 * (int(frame) - 12), 800, 400, 400);
		} else if (frame >= 18 && frame <= 23) {
			sprite_rect = IntRect(400 * (int(frame) - 18), 1200, 400, 400); 
		}
		rect_collis->setBounds(IntRect(pos.x + 25, pos.y + 60, sprite_rect.width - 50, sprite_rect.height - 50));
	}
}

void Meteor::isReachedPoint(float time) {
	Vector2f C;

	if (current_len < full_len) {
		C = (mouse_point - start_point);
		C.x = C.x * (current_len / full_len);
		C.y = C.y * (current_len / full_len);
		C = start_point + C;
		pos_meteor.x = C.x - (120.f / 2.f);
		pos_meteor.y = C.y - (120.f / 2.f);
		current_len += 3.6 * time;
	} else {
		reached_point = true;
	}
}

void Meteor::render(RenderWindow& wd, Sprite* ptr_sprite, Sprite* ptr_sprite_meteor) noexcept {
	if (visible) {
		if (reached_point) {
			ptr_sprite->setPosition(pos.x, pos.y);
			ptr_sprite->setTextureRect(sprite_rect);
			wd.draw(*ptr_sprite);
		} else {
			ptr_sprite_meteor->setPosition(pos_meteor.x, pos_meteor.y);
			wd.draw(*ptr_sprite_meteor);
		}
	}
}
//--------------------------------------Метеорит-Meteor-Конец------------------------------------