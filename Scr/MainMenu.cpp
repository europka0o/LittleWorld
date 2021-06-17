#include "MainMenu.hpp"

//------------------------Главное-меню-main_menu-Начало---------------------------------------
main_menu::main_menu(configuration* cf, const Font& font, const Color& maincl) {
	main = new RectangleShape;
	main->setSize(Vector2f(500, cf->screenHeight));
	main->setFillColor(maincl);
	main->setPosition(0, 0);

	btStart = new __interface_companents::button(0, 0, font, L"Новая игра", Color::Black, Color::Yellow, Color::Yellow);
	btStartTren = new __interface_companents::button(0, 0, font, L"Пройти обучение", Color::Black, Color::Yellow, Color::Yellow);
	btOptions = new __interface_companents::button(0, 0, font, L"Настройки", Color::Black, Color::Yellow, Color::Yellow);
	btExit = new __interface_companents::button(0, 0, font, L"Выйти", Color::Black, Color::Yellow, Color::Yellow);

	btStart->setPosition((main->getGlobalBounds().width / 2) - (btStart->getSize().width / 2), main->getGlobalBounds().top + 340);
	btStartTren->setPosition((main->getGlobalBounds().width / 2) - (btStartTren->getSize().width / 2), main->getGlobalBounds().top + 440);
	btOptions->setPosition((main->getGlobalBounds().width / 2) - (btOptions->getSize().width / 2), main->getGlobalBounds().top + 540);
	btExit->setPosition((main->getGlobalBounds().width / 2) - (btExit->getSize().width / 2), main->getGlobalBounds().top + 640);


	txMainMenu = new __interface_companents::text_box(font, 0, 0, L"Главное меню", Color::Yellow, Color::Black);
	txMainMenu->visible_bevel = false;
	grFirst = new __interface_companents::gradient(FloatRect(Vector2f(0, 0), Vector2f(100, 5)), __interface_companents::gradient_direction::rightOnLeft, Color::Transparent, Color::Yellow);
	grSecond = new __interface_companents::gradient(FloatRect(Vector2f(0, 0), Vector2f(100, 5)), __interface_companents::gradient_direction::leftOnRight, Color::Transparent, Color::Yellow);

	txMainMenu->setPosition((main->getGlobalBounds().width / 2) - (txMainMenu->getSize().width / 2), main->getGlobalBounds().height - 100);
	grFirst->setPosition(txMainMenu->getPosition().x - 5 - grFirst->getSize().width, txMainMenu->getPosition().y + (txMainMenu->getSize().height / 2) - (grFirst->getSize().height / 2));
	grSecond->setPosition(txMainMenu->getPosition().x + 5 + txMainMenu->getSize().width, txMainMenu->getPosition().y + (txMainMenu->getSize().height / 2) - (grSecond->getSize().height / 2));
}

main_menu::~main_menu() {
	delete main;
	delete btStart, btOptions, btExit, btStartTren;
	delete txMainMenu;
	delete grFirst, grSecond;
}

void main_menu::render(RenderWindow& wd) noexcept {
	wd.draw(*main);
	btStart->render(wd);
	btStartTren->render(wd);
	btOptions->render(wd);
	btExit->render(wd);

	txMainMenu->render(wd);
	grFirst->render(wd);
	grSecond->render(wd);
}
//------------------------Главное-меню-main_menu-Конец----------------------------------------
