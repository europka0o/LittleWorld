#include "Knight.hpp"

// ----------------------------------Рыцарь-Knight-Начало------------------------------
Knight::Knight(const Sprite& ptr_sprite, float X_POS, float Y_POS, int hp, unsigned int descendant) :
	BaseCharacter(ptr_sprite, X_POS, Y_POS, hp, descendant)
	{
	direction = direcrion4::non;
	last_direction = direction;
	sprite_rect = IntRect(400 * int(frame), 250, 300, 250);
	*rect_collis = CollisionBox{ IntRect(pos.x, pos.y, abs(sprite_rect.width) - 20, abs(sprite_rect.height) - 20) };
	HP = new __interface_companents::min_bar(pos.x + (abs(sprite_rect.width) / 2), pos.y + abs(sprite_rect.height), health, 0, Color::Black, Color::Red);
}

Knight::~Knight() {
	delete HP;
}

void __fastcall Knight::setPosition(float x, float y) noexcept {
	pos.x = x;
	pos.y = y;
	rect_collis->setPosition(pos.x, pos.y);
	HP->setPosition(pos.x + (abs(sprite_rect.width) / 2) - (HP->getSize().width / 2) + 25, pos.y + abs(sprite_rect.height));
}

void Knight::setPosition(const axes_f& xy) noexcept {
	pos = xy;
	rect_collis->setPosition(pos.x, pos.y);
	HP->setPosition(pos.x + (abs(sprite_rect.width) / 2) - (HP->getSize().width / 2) + 25, pos.y + abs(sprite_rect.height));
}

void __fastcall Knight::move(float time, direcrion4 direct) noexcept {
	direction = direct;

	if (health <= 0 && !zeroing) {
		zeroing = true;
		frame = 0;
	}

	if (health <= 0) {
		frame += 0.04 * time;
		if (frame > 7) {
			frame = 6;
			is_dead = true;
		}
		sprite_rect = IntRect(400 * int(frame) + 400, 0, -400, 250);
	} else {
		switch (direction) {
			case direcrion4::right:
				frame += 0.023 * time;
				if (frame > 7) {
					frame = 0;
				}
				sprite_rect = IntRect(400 * int(frame), 250, 400, 250);
				pos.x = pos.x + (0.5 * time); break;
			case direcrion4::left:
				frame += 0.023 * time;
				if (frame > 7) {
					frame = 0;
				}
				sprite_rect = IntRect(400 * int(frame) + 400, 250, -400, 250);
				pos.x = pos.x + (-0.5 * time); break;
			default: break;
		}
	}
	last_direction = direction;
	direction = direcrion4::non;

	HP->setPosition(pos.x + (abs(sprite_rect.width) / 2) - (HP->getSize().width / 2) + 25, pos.y + abs(sprite_rect.height));
	rect_collis->setPosition(pos.x + 100, pos.y + 20);
}

void __fastcall Knight::attack(float time) {
	if (health <= 0 && !zeroing) {
		zeroing = true;
		frame = 0;
	}

	if (health <= 0) {
		frame += 0.023 * time;
		if (frame > 7) {
			frame = 6;
			is_dead = true;
		}
		sprite_rect = IntRect(400 * int(frame) + 400, 0, -400, 250);
	} else {
		frame += 0.023 * time;
		if (frame > 7) {
			frame = 0;
		}
		sprite_rect = IntRect(400 * int(frame) + 400, 500, -400, 250);
	}
}

bool Knight::isCooldown(float time) {
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

void Knight::render(RenderWindow& wd, Sprite* ptr_sprite) noexcept {
	if (visible) {
		ptr_sprite->setPosition(pos.x, pos.y);
		ptr_sprite->setTextureRect(sprite_rect);
		wd.draw(*ptr_sprite);
		HP->changeBar(health);
		HP->render(wd);
	}
}
//----------------------------------Рыцарь-Knight-Конец------------------------------