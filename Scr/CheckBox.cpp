#include "CheckBox.hpp"

//------------------------------Чекбокс-check_box-Начало--------------------------------------
__interface_companents::check_box::check_box(int x, int y, const Color& maincl, const Color& bordercl, const Color& checkcl) :
	BaseInerface(x, y, FloatRect(Vector2f(0, 0), Vector2f(0, 0))),
	isCheck(false)
{
	//main_cl = new Color;
	//*main_cl = maincl;
	main = new RectangleShape;
	main->setSize(Vector2f(24, 24));
	main->setFillColor(maincl);
	main->setPosition(pos.x + 2, pos.y + 2);

	//border_cl = new Color;
	//*border_cl = bordercl;
	border = new RectangleShape;
	border->setSize(Vector2f(28, 28));
	border->setFillColor(bordercl);
	border->setPosition(pos.x, pos.y);

	//check_cl = new Color;
	//*check_cl = checkcl;
	check = new RectangleShape;
	check->setSize(Vector2f(20, 20));
	check->setFillColor(checkcl);
	check->setPosition(pos.x + 4, pos.y + 4);

	fl_rect = border->getGlobalBounds();
}

__interface_companents::check_box::~check_box() {
	delete main, border, check;
}

void __interface_companents::check_box::setPosition(const axes_i& xy) {
	pos = xy;

	border->setPosition(pos.x, pos.y);
	main->setPosition(pos.x + 2, pos.y + 2);
	check->setPosition(pos.x + 4, pos.y + 4);
	fl_rect = border->getGlobalBounds();
}

void __fastcall __interface_companents::check_box::setPosition(int x, int y) {
	pos.x = x;
	pos.y = y;

	border->setPosition(pos.x, pos.y);
	main->setPosition(pos.x + 2, pos.y + 2);
	check->setPosition(pos.x + 4, pos.y + 4);
	fl_rect = border->getGlobalBounds();
}

void __interface_companents::check_box::render(RenderWindow& wd) noexcept {
	if (visible) {
		wd.draw(*border);
		wd.draw(*main);
		if (isCheck) {
			wd.draw(*check);
		}
	}
}

void __interface_companents::check_box::invers(bool operation) {
	isCheck = operation;
}

void __interface_companents::check_box::invers() {
	isCheck = isCheck ? false : true;
}
//------------------------------Чекбокс-check_box-Конец---------------------------------------