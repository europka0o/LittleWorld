#include "ComboBox.hpp"

//----------------------------Комбо-бокс-combo_box-Начало---------------------------------------
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
	(*it)->first.setPosition(pos.x, pos.y);
	(*it)->first.setPosition(repoz_x(float, pos.x, (*it)->first.getGlobalBounds().left, 5), repoz_y(float, pos.y, (*it)->first.getGlobalBounds().top, 5));

	fl_rect = main->getGlobalBounds();
}

void __fastcall __interface_companents::combo_box::setPosition(int x, int y) {
	pos.x = x;
	pos.y = y;

	main->setPosition(pos.x, pos.y);
	(*it)->first.setPosition(pos.x, pos.y);
	(*it)->first.setPosition(repoz_x(int, pos.x, (*it)->first.getGlobalBounds().left, 5), repoz_y(int, pos.y, (*it)->first.getGlobalBounds().top, 5));

	fl_rect = main->getGlobalBounds();
}

void __interface_companents::combo_box::add(const wchar_t* st, int val) {
	mass_text.push_back(new std::pair{ Text(st, *font, __interface_companents::text_size::small_t), val });
	it = mass_text.end();
	it--;
	(*it)->first.setFillColor(text_cl);
	(*it)->first.setPosition(pos.x, pos.y);
	(*it)->first.setPosition(repoz_x(int, pos.x, (*it)->first.getGlobalBounds().left, 5), repoz_y(int, pos.y, (*it)->first.getGlobalBounds().top, 5));
	main->setSize(Vector2f((*it)->first.getGlobalBounds().width + 10, (*it)->first.getGlobalBounds().height + 10));
	fl_rect = main->getGlobalBounds();
}

void __interface_companents::combo_box::add(const std::pair<Text, int>&& _cell) {
	mass_text.push_back(new std::pair{ _cell });
	it = mass_text.end();
	it--;
	(*it)->first.setFillColor(text_cl);
	(*it)->first.setPosition(pos.x, pos.y);
	(*it)->first.setPosition(repoz_x(int, pos.x, (*it)->first.getGlobalBounds().left, 5), repoz_y(int, pos.y, (*it)->first.getGlobalBounds().top, 5));
	main->setSize(Vector2f((*it)->first.getGlobalBounds().width + 10, (*it)->first.getGlobalBounds().height + 10));
	fl_rect = main->getGlobalBounds();
}

void __interface_companents::combo_box::next() {
	it++;
	if (it == mass_text.end()) {
		it = mass_text.begin();
	}

	if (active) {
		(*it)->first.setFillColor(Color::Black);
	} else {
		(*it)->first.setFillColor(Color::Yellow);
	}

	main->setSize(Vector2f((*it)->first.getGlobalBounds().width + 10, (*it)->first.getGlobalBounds().height + 10));
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
		(*it)->first.setFillColor(Color::Black);
	} else {
		(*it)->first.setFillColor(Color::Yellow);
	}

	main->setSize(Vector2f((*it)->first.getGlobalBounds().width + 10, (*it)->first.getGlobalBounds().height + 10));
	fl_rect = main->getGlobalBounds();
}

const std::wstring __interface_companents::combo_box::getText() const noexcept {
	return std::wstring((*it)->first.getString().begin(), (*it)->first.getString().end());
}

int __interface_companents::combo_box::getValue() const noexcept {
	return (*it)->second;
}

bool __fastcall __interface_companents::combo_box::isAction(int x, int y) {
	fl_rect.contains(x, y) ? active = true : active = false;
	if (active) {
		(*it)->first.setFillColor(Color::Black);
		visible_main = true;
	} else {
		(*it)->first.setFillColor(Color::Yellow);
		visible_main = false;
	}
	return active;
}

bool __interface_companents::combo_box::isAction(const axes_i& xy) {
	fl_rect.contains(xy.x, xy.y) ? active = true : active = false;
	if (active) {
		(*it)->first.setFillColor(Color::Black);
		visible_main = true;
	} else {
		(*it)->first.setFillColor(Color::Yellow);
		visible_main = false;
	}
	return active;
}

void __interface_companents::combo_box::render(RenderWindow& wd) noexcept {
	if (visible) {
		if (visible_main) {
			wd.draw(*main);
		}
		wd.draw((*it)->first);
	}
}
//-----------------------------Комбо-бокс-combo_box-Конец---------------------------------------