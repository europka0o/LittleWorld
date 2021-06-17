#include "MultilineText.hpp"

//-----------------------------------Многострочный-текст-multiline_text-Конец-------------------------------------
__interface_companents::multiline_text::multiline_text(float x, float y, const Color& lbcol, const Color& bvcol) :
	visible(true),
	visible_bevel(true)
{
	pos.x = x;
	pos.y = y;
	font_main = new Font;
	font_main->loadFromFile("Img/18094.ttf");
	SIZE_MSTX = 0;
	max_length = 0;

	bevel_cl = new Color;
	*bevel_cl = bvcol;
	label_cl = new Color;
	*label_cl = lbcol;

	bevel = new RectangleShape;
}

__interface_companents::multiline_text::~multiline_text() noexcept {
	if (SIZE_MSTX > 0) {
		for (dyn_vector_text::iterator it_ms = mass_string.begin(); it_ms != mass_string.end();) {
			delete* it_ms;
			it_ms = mass_string.erase(it_ms);
		}
		mass_string.shrink_to_fit();
	}
	delete font_main, bevel, bevel_cl, label_cl;
}

void __interface_companents::multiline_text::add(const std::wstring& txt) noexcept {
	float rep_y = 0;
	int height = 0;
	++SIZE_MSTX;
#undef small
	mass_string.push_back(new Text());
	mass_string.back()->setFont(*font_main);
	mass_string.back()->setString(txt);
	mass_string.back()->setCharacterSize(text_size::small_t);
	mass_string.back()->setFillColor(*label_cl);

	for (int i = 0; i < SIZE_MSTX; i++) {
		if (i == 0) {
			mass_string[i]->setPosition(pos.x, pos.y);
			max_length = mass_string[i]->getGlobalBounds().width;
			mass_string[i]->setPosition(repoz_x(float, pos.x, mass_string[i]->getGlobalBounds().left, 5), repoz_y(float, pos.y, mass_string[i]->getGlobalBounds().top, 5));
			height += mass_string[i]->getGlobalBounds().height;
		}
		else {
			mass_string[i]->setPosition(pos.x, pos.y);
			max_length < mass_string[i]->getGlobalBounds().width ? max_length = mass_string[i]->getGlobalBounds().width : max_length;
			rep_y = repoz_y(float, pos.y, mass_string[i]->getGlobalBounds().top, 5);
			rep_y += (height + 5 * i);
			mass_string[i]->setPosition(repoz_x(float, pos.x, mass_string[i]->getGlobalBounds().left, 5), rep_y);
			height += mass_string[i]->getGlobalBounds().height;
		}
	}

	bevel->setSize(Vector2f(max_length + 10, height + (SIZE_MSTX * 5) + 5));
	bevel->setFillColor(*bevel_cl);
	bevel->setPosition(pos.x, pos.y);


}

void __interface_companents::multiline_text::resize(int size) noexcept {
	float rep_y = 0;
	int height = 0;
	for (int i = 0; i < SIZE_MSTX; i++) {
		if (i == 0) {
			mass_string[i]->setCharacterSize(size);
			mass_string[i]->setPosition(pos.x, pos.y);
			max_length = mass_string[i]->getGlobalBounds().width;
			mass_string[i]->setPosition(repoz_x(float, pos.x, mass_string[i]->getGlobalBounds().left, 5), repoz_y(float, pos.y, mass_string[i]->getGlobalBounds().top, 5));
			height += mass_string[i]->getGlobalBounds().height;
		}
		else {
			mass_string[i]->setCharacterSize(size);
			mass_string[i]->setPosition(pos.x, pos.y);
			max_length < mass_string[i]->getGlobalBounds().width ? max_length = mass_string[i]->getGlobalBounds().width : max_length;
			rep_y = repoz_y(float, pos.y, mass_string[i]->getGlobalBounds().top, 5);
			rep_y += (height + 5 * i);
			mass_string[i]->setPosition(repoz_x(float, pos.x, mass_string[i]->getGlobalBounds().left, 5), rep_y);
			height += mass_string[i]->getGlobalBounds().height;
		}
	}

	bevel->setSize(Vector2f(max_length + 10, height + (SIZE_MSTX * 5) + 5));
	bevel->setFillColor(*bevel_cl);
	bevel->setPosition(pos.x, pos.y);
}

void __interface_companents::multiline_text::render(RenderWindow& wd) noexcept {
	if (visible) {
		wd.draw(*bevel);
		for (int i = 0; i < SIZE_MSTX; i++) {
			wd.draw(*mass_string[i]);
		}
	}
}
//-----------------------------------Многострочный-текст-multiline_text-Конец-------------------------------------