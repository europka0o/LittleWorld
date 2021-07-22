#include "IceBall.hpp"

//---------------------------------------Ледяной-шар-IceBall-Начало------------------------------------------
IceBall::IceBall(const Sprite &ptr_sprite, float X_POS, float Y_POS, int hp, unsigned int descendant) :
	BaseCharacter(ptr_sprite, X_POS, Y_POS, hp, descendant)
	{
	sprite_rect = IntRect(0, 0, 400, 120); //fl_rect = sprt->getGlobalBounds();
	*rect_collis = CollisionBox{ IntRect(pos.x, pos.y, 120, abs(sprite_rect.height)) };

	HP = new __interface_companents::min_bar(pos.x + (abs(sprite_rect.width) / 2) - 200, pos.y + abs(sprite_rect.height), health, 0, Color::Black, Color::Green);
}

IceBall::~IceBall() {
	delete HP;
}

void __fastcall IceBall::setPosition(float x, float y) noexcept {
	pos.x = x;
	pos.y = y;
	rect_collis->setPosition(pos.x, pos.y);
	HP->setPosition(pos.x + (abs(sprite_rect.width) / 2) - 200, pos.y + abs(sprite_rect.height));
}

void IceBall::setPosition(const axes_f &xy) noexcept {
	pos = xy;
	rect_collis->setPosition(pos.x, pos.y);
	HP->setPosition(pos.x + (abs(sprite_rect.width) / 2) - 200, pos.y + abs(sprite_rect.height));
}

void __fastcall IceBall::update(float time) noexcept {
	if (health <= 0 && !zeroing) {
		zeroing = true;
		frame = 0;
	}

	if (health <= 0) {
		frame += 0.023 * time;
		if (frame > 5) {
			frame = 4;
			is_dead = true;
		}
		sprite_rect = IntRect(400 * int(frame), 120, 400, 120); //sprt->setTextureRect(IntRect(400 * int(frame), 120, 400, 120));
	} else {
		frame += 0.023 * time;
		if (frame > 5) {
			frame = 0;
		}
		sprite_rect = IntRect(400 * int(frame), 0, 400, 120); //sprt->setTextureRect(IntRect(400 * int(frame), 0, 400, 120));
	}	
}

bool IceBall::isCooldown(float time) {
	if (!cooldown) {
		timer_cooldown = 0;
		return false;
	} else {
		timer_cooldown += time;
		if (timer_cooldown >= 1.4) {
			cooldown = false;
			timer_cooldown = 0;
			return false;
		}
		cooldown = true;
		return true;
	}
}

void __fastcall move(float time, direcrion4 direct = direcrion4::non) noexcept {
	return;
}

void __fastcall attack(float time) {
	return;
}

void IceBall::render(RenderWindow &wd, Sprite* ptr_sprite) noexcept {
	if (visible) {
		ptr_sprite->setPosition(pos.x, pos.y);
		ptr_sprite->setTextureRect(sprite_rect);
		wd.draw(*ptr_sprite);
		HP->changeBar(health);
		HP->render(wd);
	}
}
//--------------------------------------Ледяной-шар-IceBall-Конец------------------------------------------