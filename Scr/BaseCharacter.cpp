#include "BaseCharacter.hpp"

//--------------------------------База-Характера-BaseCharacter-Начало------------------------------------------
BaseCharacter::BaseCharacter() :
	pos(axes_f(0, 0)),
	health(0),
	visible(true),
	cooldown(false),
	is_dead(false),
	zeroing(false),
	timer_cooldown(0),
	frame(0),
	descendant_class(DEFULT_CLASS)
{
	rect_collis = new CollisionBox(IntRect(pos.x, pos.y, 0, 0));
}

BaseCharacter::BaseCharacter(const Sprite& ptr_sprite, float x, float y, int _hp, unsigned int descendant) :
	pos(x, y),
	health(_hp),
	visible(true),
	cooldown(false),
	is_dead(false),
	zeroing(false),
	timer_cooldown(0),
	frame(0),
	descendant_class(descendant)
{
	sprite_rect = static_cast<IntRect>(ptr_sprite.getGlobalBounds());
	rect_collis = new CollisionBox(IntRect(pos.x, pos.y, abs(sprite_rect.width), abs(sprite_rect.height)));
}

BaseCharacter::BaseCharacter(const Sprite& ptr_sprite, const axes_f& xy, int _hp, unsigned int descendant) :
	pos(xy),
	health(_hp),
	visible(true),
	cooldown(false),
	is_dead(false),
	zeroing(false),
	timer_cooldown(0),
	frame(0),
	descendant_class(descendant)
{
	sprite_rect = static_cast<IntRect>(ptr_sprite.getGlobalBounds());
	rect_collis = new CollisionBox(IntRect(pos.x, pos.y, abs(sprite_rect.width), abs(sprite_rect.height)));
}

BaseCharacter::~BaseCharacter() {
	delete rect_collis;
}

const axes_f& BaseCharacter::getPosition() const noexcept {
	return pos;
}

const IntRect& BaseCharacter::getSize() const noexcept {
	return sprite_rect;
}

void BaseCharacter::setPosition(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void BaseCharacter::setPosition(const axes_f& xy) {
	pos = xy;
}

void __fastcall BaseCharacter::move(float time, direcrion4 direct) noexcept {
	return;
}

void __fastcall BaseCharacter::attack(float time) {
	return;
}

bool BaseCharacter::isCooldown(float time) {
	return false;
}

void BaseCharacter::render(RenderWindow& wd, Sprite* ptr_sprite) noexcept {
	if (visible) {
		ptr_sprite->setPosition(pos.x, pos.y);
		ptr_sprite->setTextureRect(sprite_rect);
		wd.draw(*ptr_sprite);
	}
}
//--------------------------------База-Характера-BaseCharacter-Конец------------------------------------------