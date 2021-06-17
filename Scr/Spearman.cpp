#include "Spearman.hpp"

//-----------------------------------------Копейщик-Spearman-Начало------------------------------------------
Spearman::Spearman(const Sprite& ptr_sprite, float X_POS, float Y_POS, int hp, unsigned int descendant) :
	BaseCharacter(ptr_sprite, X_POS, Y_POS, hp, descendant)
	{
	direction = direcrion4::non;
	last_direction = direction;
	sprite_rect = IntRect(300 * int(frame), 0, 300, 180);
	*rect_collis = CollisionBox{ IntRect(pos.x + 15, pos.y, abs(sprite_rect.width) - 30, abs(sprite_rect.height)) };
	HP = new __interface_companents::min_bar(pos.x + (sprite_rect.width / 2), pos.y + sprite_rect.height, health, 0, Color::Black, Color::Red);
}

Spearman::~Spearman() {
	delete rect_collis, HP;
}

void __fastcall Spearman::setPosition(float x, float y) noexcept {
	pos.x = x;
	pos.y = y;
	rect_collis->setPosition(pos.x + 15, pos.y);
	HP->setPosition(pos.x + (abs(sprite_rect.width) / 2) - (HP->getSize().width / 2) + 20, pos.y + abs(sprite_rect.height));
}

void Spearman::setPosition(const axes_f& xy) noexcept {
	pos = xy;
	rect_collis->setPosition(pos.x + 15, pos.y);
	HP->setPosition(pos.x + (abs(sprite_rect.width) / 2) - (HP->getSize().width / 2) + 20, pos.y + abs(sprite_rect.height));
}

void __fastcall Spearman::move(float time, direcrion4 direct) noexcept {
	direction = direct;

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
		sprite_rect = IntRect(300 * int(frame) + 300, 360, -300, 180);
	} else {
		switch (direction) { //Направление движения
			case direcrion4::right:
				frame += 0.023 * time;
				if (frame > 7) {
					frame = 0;
				}
				sprite_rect = IntRect(300 * int(frame), 0, 300, 180);
				pos.x = pos.x + (0.5 * time); break;
			case direcrion4::left:
				frame += 0.023 * time;
				if (frame > 7) {
					frame = 0;
				}
				sprite_rect = IntRect(300 * int(frame) + 300, 0, -300, 180);
				pos.x = pos.x + (-0.5 * time); break;
			default: break;
		}
	}
	last_direction = direction;
	direction = direcrion4::non;
	HP->setPosition(pos.x + (abs(sprite_rect.width) / 2) - (HP->getSize().width / 2) + 20, pos.y + abs(sprite_rect.height));
	rect_collis->setPosition(pos.x + 15, pos.y);
}

void __fastcall Spearman::attack(float time) {
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
		sprite_rect = IntRect(300 * int(frame) + 300, 360, -300, 180);
	} else {
		frame += 0.023 * time;
		if (frame > 6) {
			frame = 0;
		}
		sprite_rect = IntRect(300 * int(frame) + 300, 180, -300, 180);
	}
}

bool Spearman::isCooldown(float time) {
	if (!cooldown) {
		timer_cooldown = 0;
		return false;
	} else {
		timer_cooldown += time;
		if (timer_cooldown >= 2) {
			cooldown = false;
			timer_cooldown = 0;
			return false;
		}
		cooldown = true;
		return true;
	}
}

void Spearman::render(RenderWindow& wd, Sprite* ptr_sprite) noexcept {
	if (visible) {
		ptr_sprite->setPosition(pos.x, pos.y);
		ptr_sprite->setTextureRect(sprite_rect);
		wd.draw(*ptr_sprite);
		HP->changeBar(health);
		HP->render(wd);
	}
}
//------------------------------------------Копейщик-Spearman-Конец------------------------------------------
