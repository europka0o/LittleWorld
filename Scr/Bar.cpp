#include "Bar.hpp"

//-----------------------------------Полоса-bar-Начало-------------------------------------
__interface_companents::bar::bar(const Font& font, int x, int y, int br_ma, int br_mi, const wchar_t* name, const Color& mcol, const Color& bcol, const Color& tcol) :
	BaseInerface(x, y, FloatRect(Vector2f(0, 0), Vector2f(0, 0))),
	max_bar(br_ma),
	min_bar(br_mi),
	curr_bar(br_ma)
{
	label = new Text;
	label->setFont(font);
	label->setString(name);
	label->setCharacterSize(small_t);
	label->setFillColor(tcol);
	label->setPosition(pos.x, pos.y);
	label->setPosition(repoz_x(float, pos.x, label->getGlobalBounds().left, 5), repoz_y(float, pos.y, label->getGlobalBounds().top, 5));

	main = new RectangleShape;
	main->setSize(Vector2f(label->getGlobalBounds().width + 420, label->getGlobalBounds().height + 10));
	main->setFillColor(mcol);
	main->setPosition(pos.x, pos.y);

	bevel = new RectangleShape;
	bevel->setSize(Vector2f(400, label->getGlobalBounds().height));
	bevel->setFillColor(bcol);
	bevel->setPosition(label->getGlobalBounds().width + 10 + 5, pos.y + 5);

	fl_rect = main->getGlobalBounds();
}

__interface_companents::bar::bar() :
	BaseInerface(0, 0, FloatRect(Vector2f(0, 0), Vector2f(0, 0))),
	max_bar(100),
	min_bar(0),
	curr_bar(100)
{
	label = new Text;
	main = new RectangleShape;
	bevel = new RectangleShape;
}

__interface_companents::bar::~bar() {
	delete label, main, bevel;
}

void __fastcall __interface_companents::bar::changeBar(int arg) noexcept {
	if (curr_bar != arg) {
		if (arg < 0) {
			arg = 0;
		}
		bevel->setSize(Vector2f(static_cast<unsigned long long>(400 * arg) / max_bar, label->getGlobalBounds().height));
		curr_bar = arg;
	}
}

void __interface_companents::bar::render(RenderWindow& wd) noexcept {
	if (visible) {
		wd.draw(*main);
		wd.draw(*bevel);
		wd.draw(*label);
	}
}

void __fastcall __interface_companents::bar::setPosition(int x, int y) noexcept {
	pos.x = x;
	pos.y = y;
	main->setPosition(pos.x, pos.y);
	bevel->setPosition(pos.x + label->getGlobalBounds().width + 10 + 5, pos.y + 5);
	label->setPosition(pos.x, pos.y);
	label->setPosition(repoz_x(float, pos.x, label->getGlobalBounds().left, 5), repoz_y(float, pos.y, label->getGlobalBounds().top, 5));

	fl_rect = main->getGlobalBounds();
}

void __interface_companents::bar::setPosition(const axes_i& xy) noexcept {
	pos = xy;
	main->setPosition(pos.x, pos.y);
	bevel->setPosition(pos.x + label->getGlobalBounds().width + 10 + 5, pos.y + 5);
	label->setPosition(pos.x, pos.y);
	label->setPosition(repoz_x(float, pos.x, label->getGlobalBounds().left, 5), repoz_y(float, pos.y, label->getGlobalBounds().top, 5));

	fl_rect = main->getGlobalBounds();
}

void __interface_companents::bar::freeze(Camera* camera, const axes_i& xy) noexcept {
	this->setPosition(camera->getPosition().x - (camera->getScreenWidth() / 2) + xy.x, camera->getPosition().y - (camera->getScreenHeight() / 2) + xy.y);
}

void __interface_companents::bar::freeze(Camera* camera, int x, int y) noexcept {
	this->setPosition(camera->getPosition().x - (camera->getScreenWidth() / 2) + x, camera->getPosition().y - (camera->getScreenHeight() / 2) + y);
}

void __interface_companents::bar::resize(int size) noexcept {
	label->setCharacterSize(size);
	label->setPosition(pos.x, pos.y);
	label->setPosition(repoz_x(float, pos.x, label->getGlobalBounds().left, 5), repoz_y(float, pos.y, label->getGlobalBounds().top, 5));
	main->setSize(Vector2f(label->getGlobalBounds().width + 420, label->getGlobalBounds().height + 10));
	bevel->setSize(Vector2f((400 * curr_bar) / max_bar, label->getGlobalBounds().height));
	bevel->setPosition(label->getGlobalBounds().width + 10 + 5, pos.y + 5);

	fl_rect = main->getGlobalBounds();
}
//-----------------------------------Полоса-bar-Конец--------------------------------------