#include "ComboBox.hpp"

//----------------------------Комбо-бокс-combo_box-Начало---------------------------------------
__interface_companents::combo_box::cell::cell(Text txt, int val) :
	text_box(txt),
	value(val)
{

}

__interface_companents::combo_box::combo_box(int x, int y, const Color& maincl, const Color& textcl) :
	BaseInerface(x, y, FloatRect(Vector2f(0, 0), Vector2f(0, 0))),
	visible_main(false),
	active(false)
{
	font = new Font;
	font->loadFromFile("Img/18094.ttf");

	text_cl = textcl;
	main_cl = maincl;

	main = new RectangleShape;
	main->setSize(Vector2f(0, 0));
	main->setFillColor(main_cl);
	main->setPosition(pos.x, pos.y);

	fl_rect = main->getGlobalBounds();

	it = mass_text.begin();
}

__interface_companents::combo_box::~combo_box() {
	delete main;

	for (it = mass_text.begin(); it != mass_text.end(); it++) {
		delete* it;
	}

	mass_text.clear();
}

void __interface_companents::combo_box::setPosition(const axes_i& xy) {
	pos = xy;

	main->setPosition(pos.x, pos.y);
	(*it)->text_box.setPosition(pos.x, pos.y);
	(*it)->text_box.setPosition(repoz_x(int, pos.x, (*it)->text_box.getGlobalBounds().left, 5), repoz_y(int, pos.y, (*it)->text_box.getGlobalBounds().top, 5));

	fl_rect = main->getGlobalBounds();
}

void __fastcall __interface_companents::combo_box::setPosition(int x, int y) {
	pos.x = x;
	pos.y = y;

	main->setPosition(pos.x, pos.y);
	(*it)->text_box.setPosition(pos.x, pos.y);
	(*it)->text_box.setPosition(repoz_x(int, pos.x, (*it)->text_box.getGlobalBounds().left, 5), repoz_y(int, pos.y, (*it)->text_box.getGlobalBounds().top, 5));

	fl_rect = main->getGlobalBounds();
}

void __interface_companents::combo_box::add(const wchar_t* st, int val) {
	mass_text.push_back(new cell(Text(st, *font, __interface_companents::text_size::small_t), val));
	it = mass_text.end();
	it--;
	(*it)->text_box.setFillColor(text_cl);
	(*it)->text_box.setPosition(pos.x, pos.y);
	(*it)->text_box.setPosition(repoz_x(int, pos.x, (*it)->text_box.getGlobalBounds().left, 5), repoz_y(int, pos.y, (*it)->text_box.getGlobalBounds().top, 5));
	main->setSize(Vector2f((*it)->text_box.getGlobalBounds().width + 10, (*it)->text_box.getGlobalBounds().height + 10));
	fl_rect = main->getGlobalBounds();
}

void __interface_companents::combo_box::next() {
	it++;
	if (it == mass_text.end()) {
		it = mass_text.begin();
	}

	if (active) {
		(*it)->text_box.setFillColor(Color::Black);
	} else {
		(*it)->text_box.setFillColor(Color::Yellow);
	}

	main->setSize(Vector2f((*it)->text_box.getGlobalBounds().width + 10, (*it)->text_box.getGlobalBounds().height + 10));
	fl_rect = main->getGlobalBounds();
}

void __interface_companents::combo_box::back() {
	if (it != mass_text.begin()) {
		it--;
	} else {
		it = mass_text.end();
		it--;
	}

	if (active) {
		(*it)->text_box.setFillColor(Color::Black);
	} else {
		(*it)->text_box.setFillColor(Color::Yellow);
	}

	main->setSize(Vector2f((*it)->text_box.getGlobalBounds().width + 10, (*it)->text_box.getGlobalBounds().height + 10));
	fl_rect = main->getGlobalBounds();
}

const std::wstring __interface_companents::combo_box::getText() const noexcept {
	return std::wstring((*it)->text_box.getString().begin(), (*it)->text_box.getString().end());
}

int __interface_companents::combo_box::getValue() const noexcept {
	return (*it)->value;
}

bool __fastcall __interface_companents::combo_box::isAction(int x, int y) {
	fl_rect.contains(x, y) ? active = true : active = false;
	if (active) {
		(*it)->text_box.setFillColor(Color::Black);
		visible_main = true;
	} else {
		(*it)->text_box.setFillColor(Color::Yellow);
		visible_main = false;
	}
	return active;
}

bool __interface_companents::combo_box::isAction(const axes_i& xy) {
	fl_rect.contains(xy.x, xy.y) ? active = true : active = false;
	if (active) {
		(*it)->text_box.setFillColor(Color::Black);
		visible_main = true;
	} else {
		(*it)->text_box.setFillColor(Color::Yellow);
		visible_main = false;
	}
	return active;
}

void __interface_companents::combo_box::render(RenderWindow& wd) noexcept {
	if (visible) {
		if (visible_main) {
			wd.draw(*main);
		}
		wd.draw((*it)->text_box);
	}
}
//-----------------------------Комбо-бокс-combo_box-Конец---------------------------------------