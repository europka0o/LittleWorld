#include "Object.hpp"

//---------------------------Статический-объект-ObjectStatic-Начало------------------------------
ObjectStatic::ObjectStatic(const Sprite& ptr_sprite, float X, float Y) :
	visible(true)
{
	pos.x = X;
	pos.y = Y;

	sprite_rect = IntRect(0, 0, ptr_sprite.getGlobalBounds().width, ptr_sprite.getGlobalBounds().height);
	rect_collis = new CollisionBox(IntRect(pos.x, pos.x, ptr_sprite.getGlobalBounds().width, ptr_sprite.getGlobalBounds().height));
}

ObjectStatic::~ObjectStatic() {
	delete rect_collis;
}

const axes_i& ObjectStatic::getPosition() const noexcept {
	return pos;
}

void __fastcall ObjectStatic::setPosition(int x, int y) {
	pos.x = x;
	pos.y = y;
	rect_collis->setPosition(pos.x, pos.y);
}

void ObjectStatic::setPosition(const axes_i& xy) {
	pos = xy;
	rect_collis->setPosition(xy);
}

void ObjectStatic::render(RenderWindow& wd, Sprite* ptr_sprite) noexcept {
	if (visible) {
		ptr_sprite->setPosition(pos.x, pos.y);
		ptr_sprite->setTextureRect(sprite_rect);
		wd.draw(*ptr_sprite);
	}
}
//----------------------------------Статический-объект-ObjectStatic-Конец-------------------------------

//-------------------------------Анимированный-объект-ObjectAnimated-Начало------------------------------
ObjectAnimated::ObjectAnimated(const Sprite& ptr_sprite, float X, float Y) :
	frame(0),
	end(false),
	ObjectStatic(ptr_sprite, X, Y)
{
}

ObjectAnimated::~ObjectAnimated() {}

//void __fastcall ObjectAnimated::update(float time) {
//	return;
//}
//-------------------------------Анимированный-объект-ObjectAnimated-Конец-------------------------------