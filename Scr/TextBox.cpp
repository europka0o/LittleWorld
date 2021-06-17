#include "TextBox.hpp"

//-----------------------------------Текст-text_box-Начало-------------------------------------
__interface_companents::text_box::text_box(const Font& font, int x, int y, const wchar_t* txt, const Color& lbcol, const Color& bvcol) :
	BaseInerface(x, y, FloatRect(Vector2f(0, 0), Vector2f(0, 0))),
	visible_bevel(true)
{
	label = new Text;
	label->setFont(font);
	label->setString(txt);
	label->setCharacterSize(__interface_companents::text_size::small_t);

	//label_cl = new Color;  
	//*label_cl = lbcol;
	label->setFillColor(lbcol);
	label->setPosition(pos.x, pos.y);
	label->setPosition(repoz_x(int, pos.x, label->getGlobalBounds().left, 5), repoz_y(int, pos.y, label->getGlobalBounds().top, 5));

	bevel = new RectangleShape;
	bevel->setSize(Vector2f(label->getGlobalBounds().width + 10, label->getGlobalBounds().height + 10));
	//bevel_cl = new Color;
	//*bevel_cl = bvcol;
	bevel->setFillColor(bvcol);
	bevel->setPosition(pos.x, pos.y);

	fl_rect = bevel->getGlobalBounds();
}

__interface_companents::text_box::~text_box() {
	delete label, bevel;
}

void __interface_companents::text_box::setString(const wchar_t* txt) noexcept {
	label->setString(txt);
	__interface_companents::text_box::resize(label->getCharacterSize());
}

void __interface_companents::text_box::setFont(const Font& font) noexcept {
	label->setFont(font);
}

void __interface_companents::text_box::setPosition(const axes_i& xy) noexcept {
	pos = xy;
	bevel->setPosition(pos.x, pos.y);
	label->setPosition(pos.x, pos.y);
	label->setPosition(repoz_x(int, pos.x, label->getGlobalBounds().left, 5), repoz_y(int, pos.y, label->getGlobalBounds().top, 5));

	fl_rect = bevel->getGlobalBounds();
}

void __fastcall __interface_companents::text_box::setPosition(int x, int y) noexcept {
	pos.x = x;
	pos.y = y;
	bevel->setPosition(pos.x, pos.y);
	label->setPosition(pos.x, pos.y);
	label->setPosition(repoz_x(int, pos.x, label->getGlobalBounds().left, 5), repoz_y(int, pos.y, label->getGlobalBounds().top, 5));

	fl_rect = bevel->getGlobalBounds();
}

void __interface_companents::text_box::resize(int size) noexcept {
	label->setCharacterSize(size);
	label->setPosition(pos.x, pos.y);
	label->setPosition(repoz_x(int, pos.x, label->getGlobalBounds().left, 5), repoz_y(int, pos.y, label->getGlobalBounds().top, 5));
	bevel->setSize(Vector2f(label->getGlobalBounds().width + 10, label->getGlobalBounds().height + 10));

	fl_rect = bevel->getGlobalBounds();
}

void __interface_companents::text_box::freeze(Camera* camera, const axes_i& xy) {
	this->setPosition(camera->getPosition().x - (camera->getScreenHeight() / 2) + xy.x, camera->getPosition().y - (camera->getScreenWidth() / 2) + xy.y);
}

void __interface_companents::text_box::freeze(Camera* camera, int x, int y) {
	this->setPosition(camera->getPosition().x - (camera->getScreenHeight() / 2) + x, camera->getPosition().y - (camera->getScreenWidth() / 2) + y);
}

void __interface_companents::text_box::render(RenderWindow& wd) noexcept {
	if (visible) {
		if (visible_bevel) {
			wd.draw(*bevel);
		}
		wd.draw(*label);
	}
}
//-----------------------------------Текст-text_box-Конец-------------------------------------