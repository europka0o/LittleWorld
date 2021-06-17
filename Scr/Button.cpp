#include "Button.hpp"

//-----------------------------------Кнопка-button-Начало-------------------------------------
__interface_companents::button::button(int x, int y, const Font& font, const wchar_t* text_box, const Color& maincl, const Color& textcl, const Color& activecl) :
	BaseInerface(x, y, FloatRect(Vector2f(0, 0), Vector2f(0, 0))),
	active(false)
{
	pos.x = x;
	pos.y = y;

	txt = new Text;
	txt->setFont(font);
	txt->setString(text_box);
	txt->setCharacterSize(small_t);

	txt->setFillColor(textcl);
	txt->setPosition(pos.x, pos.y);
	txt->setPosition(repoz_x(int, pos.x, txt->getGlobalBounds().left, 5), repoz_y(int, pos.y, txt->getGlobalBounds().top, 5));

	main = new RectangleShape;
	main->setSize(Vector2f(txt->getGlobalBounds().width + 10, txt->getGlobalBounds().height + 10));
	main->setFillColor(maincl);
	main->setPosition(pos.x, pos.y);

	active_bvl = new RectangleShape;
	active_bvl->setSize(Vector2f(main->getGlobalBounds().width + 10, main->getGlobalBounds().height + 10));
	active_bvl->setFillColor(activecl);
	active_bvl->setPosition(pos.x - 5, pos.y - 5);

	fl_rect = main->getGlobalBounds();
}

__interface_companents::button::~button() {
	delete main, active_bvl, txt;
}

void __interface_companents::button::setPosition(const axes_i& xy) {
	pos = xy;
	txt->setPosition(pos.x, pos.y);
	txt->setPosition(repoz_x(int, pos.x, txt->getGlobalBounds().left, 5), repoz_y(int, pos.y, txt->getGlobalBounds().top, 5));
	main->setPosition(pos.x, pos.y);
	active_bvl->setPosition(pos.x - 5, pos.y - 5);
	fl_rect = main->getGlobalBounds();
}

void __fastcall __interface_companents::button::setPosition(int x, int y) {
	pos.x = x;
	pos.y = y;
	txt->setPosition(pos.x, pos.y);
	txt->setPosition(repoz_x(int, pos.x, txt->getGlobalBounds().left, 5), repoz_y(int, pos.y, txt->getGlobalBounds().top, 5));
	main->setPosition(pos.x, pos.y);
	active_bvl->setPosition(pos.x - 5, pos.y - 5);
	fl_rect = main->getGlobalBounds();
}

void __interface_companents::button::render(RenderWindow& wd) noexcept {
	if (visible) {
		if (active) {
			wd.draw(*active_bvl);
		}
		wd.draw(*main);
		wd.draw(*txt);
	}
}

void __interface_companents::button::resize(int size) {
	txt->setCharacterSize(size);
	txt->setPosition(pos.x, pos.y);
	txt->setPosition(repoz_x(int, pos.x, txt->getGlobalBounds().left, 5), repoz_y(int, pos.y, txt->getGlobalBounds().top, 5));
	main->setSize(Vector2f(txt->getGlobalBounds().width + 10, txt->getGlobalBounds().height + 10));
	active_bvl->setSize(Vector2f(main->getGlobalBounds().width + 10, main->getGlobalBounds().height + 10));
	fl_rect = main->getGlobalBounds();
}

void __interface_companents::button::freeze(Camera* camera, const axes_i& xy) noexcept {
	this->setPosition(camera->getPosition().x - (camera->getScreenHeight() / 2) + xy.x, camera->getPosition().y - (camera->getScreenWidth() / 2) + xy.y);

}

void __interface_companents::button::freeze(Camera* camera, int x, int y) noexcept {
	this->setPosition(camera->getPosition().x - (camera->getScreenHeight() / 2) + x, camera->getPosition().y - (camera->getScreenWidth() / 2) + y);
}

bool __fastcall __interface_companents::button::isAction(int x, int y) {
	fl_rect.contains(x, y) ? active = true : active = false;
	return active;
}

bool __interface_companents::button::isAction(const axes_i& xy) {
	fl_rect.contains(xy.x, xy.y) ? active = true : active = false;
	return active;
}
//-----------------------------------Кнопка-button-Конец--------------------------------------