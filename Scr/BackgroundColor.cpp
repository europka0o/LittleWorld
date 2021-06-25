#include "BackgroundColor.hpp"

//-------------------------------------Задний-фон-background_color-Начало------------------------------------------
background_color::background_color(int x, int y, const Color& cl, configuration* cf) :
	visible(false)
{
	pos.x = x;
	pos.y = y;

	background = new RectangleShape;
	background->setSize(Vector2f(cf->screenWidth, cf->screenHeight));
	background->setFillColor(cl);
	background->setPosition(pos.x, pos.y);
}

background_color::~background_color() {
	delete background;
}

void background_color::setColor(const Color& cl) {
	background->setFillColor(cl);
}

void background_color::render(RenderWindow& wd) noexcept {
	if (visible) {
		wd.draw(*background);
	}
}
//-------------------------------------Задний-фон-background_color-Конец------------------------------------------