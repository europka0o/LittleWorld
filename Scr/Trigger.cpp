#include "Trigger.hpp"

//-----------------------------Коллизия-CollisionBox-Начало---------------------------------------
CollisionBox::CollisionBox(const IntRect& rect) :
	active(true)
{
	pos.x = rect.left;
	pos.y = rect.top;
	rect_collis = rect;
}

CollisionBox::~CollisionBox() {}

void __fastcall CollisionBox::setPosition(int x, int y) {
	pos.x = x;
	pos.y = y;

	rect_collis.left = pos.x;
	rect_collis.top = pos.y;
}

void CollisionBox::setPosition(const axes_i& xy) {
	pos = xy;

	rect_collis.left = pos.x;
	rect_collis.top = pos.y;
}

const axes_i& CollisionBox::getPosition() const noexcept {
	return pos;
}

const IntRect& CollisionBox::getBounds() const noexcept {
	return rect_collis;
}

void CollisionBox::setBounds(const IntRect& rect) {
	pos.x = rect.left;
	pos.y = rect.top;
	rect_collis = rect;
}
//-----------------------------Коллизия-CollisionBox-Конец----------------------------------------