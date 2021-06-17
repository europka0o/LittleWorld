#include "MenuPause.hpp"

//-----------------------------------Меню-паузы-menu_pause-Начало--------------------------------------
menu_pause::menu_pause(Camera* camera, const Font& font, const Color& maincl, const Color& bordercl) :
	active(true),
	blackout_visible(true)
{
	pos = camera->getPosition();
	main = new RectangleShape;
	main->setSize(Vector2f(500, 500));
	//main_cl = new Color;
	//*main_cl = maincl;
	main->setFillColor(maincl);
	main->setPosition(pos.x - main->getGlobalBounds().width / 2, pos.y - main->getGlobalBounds().height / 2);

	border = new RectangleShape;
	border->setSize(Vector2f(main->getGlobalBounds().width + 10, main->getGlobalBounds().height + 10));
	//border_cl = new Color;
	//*border_cl = bordercl;
	border->setFillColor(bordercl);
	border->setPosition(pos.x - 5 - main->getGlobalBounds().width / 2, pos.y - 5 - main->getGlobalBounds().height / 2);

	blackout = new RectangleShape;
	blackout->setSize(Vector2f(camera->getScreenWidth(), camera->getScreenHeight()));
	blackout->setFillColor(Color(0, 0, 0, 255 / 2));
	blackout->setPosition(camera->getPosition().x - (camera->getScreenWidth() / 2), camera->getPosition().y - (camera->getScreenHeight() / 2));

	btContinue = new __interface_companents::button((main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 20, font, L"Продолжить", Color::Black, Color::Yellow, Color::Yellow);
	btOptions = new __interface_companents::button((main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 100, font, L"Настройки", Color::Black, Color::Yellow, Color::Yellow);
	btExit = new __interface_companents::button((main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 180, font, L"Выйти", Color::Black, Color::Yellow, Color::Yellow);

	txMenu = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 450, L"Меню", Color::Yellow, Color::Black);
	txMenu->visible_bevel = false;
	grFirst = new __interface_companents::gradient(FloatRect(Vector2f(100, 100), Vector2f(200, 5)), __interface_companents::gradient_direction::rightOnLeft, Color::Transparent, Color::Yellow);
	grSecond = new __interface_companents::gradient(FloatRect(Vector2f(150, 150), Vector2f(200, 5)), __interface_companents::gradient_direction::leftOnRight, Color::Transparent, Color::Yellow);
}

menu_pause::~menu_pause() {
	delete main, border, blackout;
	delete btContinue, btOptions, btExit;
	delete txMenu;
	delete grFirst, grSecond;
}

void menu_pause::render(RenderWindow& wd, Camera* camera) noexcept {

	if (active) {
		pos = camera->getPosition();

		main->setPosition(pos.x - main->getGlobalBounds().width / 2, pos.y - main->getGlobalBounds().height / 2);
		border->setPosition(pos.x - 5 - main->getGlobalBounds().width / 2, pos.y - 5 - main->getGlobalBounds().height / 2);
		btContinue->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (btContinue->getSize().width / 2), main->getGlobalBounds().top + 60);
		btOptions->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (btOptions->getSize().width / 2), main->getGlobalBounds().top + 160);
		btExit->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (btExit->getSize().width / 2), main->getGlobalBounds().top + 260);
		txMenu->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txMenu->getSize().width / 2), main->getGlobalBounds().top + 450);
		grFirst->setPosition(txMenu->getPosition().x - 5 - grFirst->getSize().width, txMenu->getPosition().y + (txMenu->getSize().height / 2) - (grSecond->getSize().height / 2));
		grSecond->setPosition(txMenu->getPosition().x + 5 + txMenu->getSize().width, txMenu->getPosition().y + (txMenu->getSize().height / 2) - (grSecond->getSize().height / 2));

		if (blackout_visible) {
			blackout->setPosition(camera->getPosition().x - (camera->getScreenWidth() / 2), camera->getPosition().y - (camera->getScreenHeight() / 2));
			wd.draw(*blackout);
		}
		wd.draw(*border);
		wd.draw(*main);

		btContinue->render(wd);
		btOptions->render(wd);
		btExit->render(wd);

		txMenu->render(wd);
		grFirst->render(wd);
		grSecond->render(wd);
	}
}
//-----------------------------------Меню-паузы-menu_pause-Конец---------------------------------------