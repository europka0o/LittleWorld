#include "DestroerCastle.hpp"

//-----------------------------------Разрушитель-замков-DestroerCastle-Начало-----------------------------------------
DestroerCastle::DestroerCastle(const Sprite& ptr_sprite, float X_POS, float Y_POS, int hp, unsigned int descendant) :
	BaseCharacter(ptr_sprite, X_POS, Y_POS, hp, descendant)
{
	direction = direcrion4::non;
	last_direction = direction;
	sprite_rect = IntRect(0, 0, 600, 350);
	*rect_collis = CollisionBox{ IntRect(pos.x, pos.y, abs(sprite_rect.width), abs(sprite_rect.height)) };
	HP = new __interface_companents::min_bar(pos.x + (abs(sprite_rect.width) / 2), pos.y + abs(sprite_rect.top), health, 0, Color::Black, Color::Red);
}

DestroerCastle::~DestroerCastle() {
	delete HP;
}

void __fastcall DestroerCastle::setPosition(float x, float y) noexcept {
	pos.x = x;
	pos.y = y;
	rect_collis->setPosition(pos.x, pos.y);
	HP->setPosition(pos.x + (abs(sprite_rect.width) / 2) - (HP->getSize().width / 2), pos.y + abs(sprite_rect.height));
}

void DestroerCastle::setPosition(const axes_f& xy) noexcept {
	pos = xy;
	rect_collis->setPosition(pos.x, pos.y);
	HP->setPosition(pos.x + (abs(sprite_rect.width) / 2) - (HP->getSize().width / 2), pos.y + abs(sprite_rect.height));
}

void __fastcall DestroerCastle::move(float time, direcrion4 direct) noexcept {
	direction = direct;

	if (health <= 0 && !zeroing) {
		zeroing = true;
		frame = 0;
	}

	if (health <= 0) {
		frame += 0.023 * time;
		if (frame > 6) {
			frame = 5;
			is_dead = true;
		}
		sprite_rect = IntRect(600 * int(frame), 700, 600, 350);
	}
	else {
		switch (direction) { //Направление движения
			case direcrion4::right:
				frame += 0.023 * time;
				if (frame > 4) {
					frame = 0;
				}
				sprite_rect = IntRect(600 * int(frame) + 600, 0, -600, 350);
				pos.x = pos.x + (0.5 * time); break;
			case direcrion4::left:
				frame += 0.023 * time;
				if (frame > 4) {
					frame = 0;
				}
				sprite_rect = IntRect(600 * int(frame), 0, 600, 350);
				pos.x = pos.x + (-0.5 * time); break;
			default: break;
		}
	}
	last_direction = direction;
	direction = direcrion4::non;
	HP->setPosition(pos.x + (abs(sprite_rect.width) / 2) - (HP->getSize().width / 2), pos.y + abs(sprite_rect.height));
	rect_collis->setPosition(pos.x, pos.y);
}

void __fastcall DestroerCastle::attack(float time) {
	if (health <= 0 && !zeroing) {
		zeroing = true;
		frame = 0;
	}

	if (health <= 0) {
		frame += 0.023 * time;
		if (frame > 6) {
			frame = 5;
			is_dead = true;
		}
		sprite_rect = IntRect(600 * int(frame), 700, 600, 350);
	} else {
		frame += 0.023 * time;
		if (frame > 6) {
			frame = 0;
		}
		sprite_rect = IntRect(600 * int(frame), 350, 600, 350);
	}
}

bool DestroerCastle::isCooldown(float time) {
	if (!cooldown) {
		timer_cooldown = 0;
		return false;
	} else {
		timer_cooldown += time;
		if (timer_cooldown >= 3) {
			cooldown = false;
			timer_cooldown = 0;
			return false;
		}
		cooldown = true;
		return true;
	}
}

void DestroerCastle::render(RenderWindow& wd, Sprite* ptr_sprite) noexcept {
	if (visible) {
		ptr_sprite->setPosition(pos.x, pos.y);
		ptr_sprite->setTextureRect(sprite_rect);
		wd.draw(*ptr_sprite);
		HP->changeBar(health);
		HP->render(wd);
	}
}
//-----------------------------------Разрушитель-замков-DestroerCastle-Конец------------------------------------------