#include "InterfBase.hpp"

//--------------------------------База-Интерфейса-BaseInterface-Начало------------------------------------------
__interface_companents::BaseInerface::BaseInerface() :
	pos(axes_i(0, 0)),
	visible(true)
{
}

__interface_companents::BaseInerface::BaseInerface(int x, int y, const FloatRect& rect) :
	pos(axes_i(x, y)),
	fl_rect(rect),
	visible(true)
{
}

__interface_companents::BaseInerface::BaseInerface(const axes_i& xy, const FloatRect& rect) :
	pos(xy),
	fl_rect(rect),
	visible(true)
{
}

__interface_companents::BaseInerface::~BaseInerface() {
	return;
}

const axes_i& __interface_companents::BaseInerface::getPosition() const noexcept {
	return pos;
}

void __interface_companents::BaseInerface::setPosition(const axes_i& xy) {
	pos = xy;
}

void __interface_companents::BaseInerface::setPosition(int x, int y) {
	pos.x = x;
	pos.y = y;
}

const FloatRect& __interface_companents::BaseInerface::getSize() const noexcept {
	return fl_rect;
}

void __interface_companents::BaseInerface::render(RenderWindow& wd) {
	return;
}
//--------------------------------База-Интерфейса-BaseInterface-Конец------------------------------------------