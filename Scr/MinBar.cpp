#include "MinBar.hpp"

//-----------------------------Мини-полоса-min_bar-Начало----------------------------------------
__interface_companents::min_bar::min_bar(int x, int y, int br_ma, int br_mi, const Color& mcol, const Color& bcol) :
	BaseInerface(x, y, FloatRect(Vector2f(0, 0), Vector2f(0, 0))),
	max_br(br_ma),
	min_br(br_mi),
	curr_br(br_ma)
{
	main = new RectangleShape;
	main->setSize(Vector2f(150, 9));
	main->setFillColor(mcol);
	main->setPosition(pos.x, pos.y);

	bevel = new RectangleShape;
	bevel->setSize(Vector2f(main->getGlobalBounds().width - 6, main->getGlobalBounds().height - 6));
	bevel->setFillColor(bcol);
	bevel->setPosition(pos.x + 3, pos.y + 3);

	fl_rect = main->getGlobalBounds();
}

__interface_companents::min_bar::~min_bar() {
	delete main, bevel;
}

void __fastcall __interface_companents::min_bar::setPosition(int x, int y) noexcept {
	pos.x = x;
	pos.y = y;

	main->setPosition(pos.x, pos.y);
	bevel->setPosition(pos.x + 3, pos.y + 3);
	fl_rect = main->getGlobalBounds();
}

void __interface_companents::min_bar::setPosition(const axes_i& xy) noexcept {
	pos = xy;

	main->setPosition(pos.x, pos.y);
	bevel->setPosition(pos.x + 3, pos.y + 3);
	fl_rect = main->getGlobalBounds();
}

void  __interface_companents::min_bar::changeBar(int arg) noexcept {
	if (curr_br != arg) {
		if (arg < 0) {
			arg = 0;
		}
		bevel->setSize(Vector2f((144 * arg) / max_br, 3));
		curr_br = arg;
	}
}

void __interface_companents::min_bar::render(RenderWindow& wd) noexcept {
	if (visible) {
		wd.draw(*main);
		wd.draw(*bevel);
	}
}
//-----------------------------Мини-полоса-min_bar-Конец-----------------------------------------
