#include "MenuSettings.hpp"

//------------------------Меню-настроек-menu_settings-Начало--------------------------------------
menu_settings::menu_settings(configuration* cf, Camera* camera, const Font& font, const Color& maincl, const Color& bordercl) :
	active(false),
	blackout_visible(false)
{
	pos = camera->getPosition();
	main = new RectangleShape;
	main->setSize(Vector2f(550, 600));
	main->setFillColor(maincl);
	main->setPosition(pos.x - main->getGlobalBounds().width / 2, pos.y - main->getGlobalBounds().height / 2);

	border = new RectangleShape;
	border->setSize(Vector2f(main->getGlobalBounds().width + 10, main->getGlobalBounds().height + 10));
	border->setFillColor(bordercl);
	border->setPosition(pos.x - 5 - main->getGlobalBounds().width / 2, pos.y - 5 - main->getGlobalBounds().height / 2);

	blackout = new RectangleShape;
	blackout->setSize(Vector2f(camera->getScreenWidth(), camera->getScreenHeight()));
	blackout->setFillColor(Color(0, 0, 0, 255 / 2));
	blackout->setPosition(camera->getPosition().x - (camera->getScreenWidth() / 2), camera->getPosition().y - (camera->getScreenHeight() / 2));

	btBack = new __interface_companents::button((main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 410, font, L"Назад", Color::Black, Color::Yellow, Color::Yellow);
	btSave = new __interface_companents::button((main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 480, font, L"Сохранить", Color::Black, Color::Yellow, Color::Yellow);

	std::string* t = new std::string(intToStr(std::string, cf->screenWidth));
	*t += " x ";
	*t += intToStr(std::string, cf->screenHeight);

	txVertS = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 20, L"Вертикальная синхронизация:", Color::Yellow, Color::Black);
	txVertS->visible_bevel = false;
	txFullS = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 80, L"На весь экран:", Color::Yellow, Color::Black);
	txFullS->visible_bevel = false;

	txAnisF = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 140, L"Анизотропная фильтрация:", Color::Yellow, Color::Black);
	txAnisF->visible_bevel = false;

	txScreen = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 200, L"Разрешение экрана:", Color::Yellow, Color::Black);
	txScreen->visible_bevel = false;
	txSound = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 260, L"Звук:", Color::Yellow, Color::Black);
	txSound->visible_bevel = false;
	txSoundV = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 320, L"Громкость звука:", Color::Yellow, Color::Black);
	txSoundV->visible_bevel = false;

	combAnisF = new __interface_companents::combo_box(txAnisF->getSize().left + txAnisF->getSize().width + 5, txAnisF->getSize().top, Color::Yellow, Color::Yellow);
	combAnisF->add(L"Выкл.", 0);
	combAnisF->add(L"2", 2);
	combAnisF->add(L"6", 6);
	combAnisF->add(L"8", 8);
	combAnisF->add(L"16", 16);

	combScreen = new __interface_companents::combo_box(txScreen->getSize().left + txScreen->getSize().width + 5, txScreen->getSize().top, Color::Yellow, Color::Yellow);
	combScreen->add(L"1280 x 720", 0);
	combScreen->add(L"1600 x 900", 1);
	combScreen->add(L"1600 x 1200", 2);
	combScreen->add(L"1920 x 1080", 3);
	combScreen->add(L"2560 x 1440", 4);

	combSoundV = new __interface_companents::combo_box(txSoundV->getSize().left + txSoundV->getSize().width + 5, txSoundV->getSize().top, Color::Yellow, Color::Yellow);
	combSoundV->add(L"0", 0);
	combSoundV->add(L"10", 10);
	combSoundV->add(L"20", 20);
	combSoundV->add(L"30", 30);
	combSoundV->add(L"40", 40);
	combSoundV->add(L"50", 50);
	combSoundV->add(L"60", 60);
	combSoundV->add(L"70", 70);
	combSoundV->add(L"80", 80);
	combSoundV->add(L"90", 90);
	combSoundV->add(L"100", 100);

	while (std::wstring(t->begin(), t->end()) != combScreen->getText()) {
		combScreen->back();
	}

	*t = intToStr(std::string, cf->soundVolume);

	while (std::wstring(t->begin(), t->end()) != combSoundV->getText()) {
		combSoundV->back();
	}

	while (cf->anisFilt != combAnisF->getValue()) {
		combAnisF->back();
	}

	cbVertS = new __interface_companents::check_box((main->getGlobalBounds().width / 2) + 0 + (txVertS->getSize().width / 2) + 5, main->getGlobalBounds().top + 20, Color::Black, Color::Yellow, Color::Yellow);
	cbVertS->isCheck = cf->verticalSync;
	cbFullS = new __interface_companents::check_box((main->getGlobalBounds().width / 2) + 0 + (txFullS->getSize().width / 2) + 5, main->getGlobalBounds().top + 100, Color::Black, Color::Yellow, Color::Yellow);
	cbFullS->isCheck = cf->fullScreen;
	cbSound = new __interface_companents::check_box((main->getGlobalBounds().width / 2) + 0 + (txVertS->getSize().width / 2) + 5, main->getGlobalBounds().top + 260, Color::Black, Color::Yellow, Color::Yellow);
	cbSound->isCheck = cf->sound;

	txMenuSettings = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 550, L"Настройки", Color::Yellow, Color::Black);
	txMenuSettings->visible_bevel = false;
	grFirst = new __interface_companents::gradient(FloatRect(Vector2f(100, 100), Vector2f(180, 5)), __interface_companents::gradient_direction::rightOnLeft, Color::Transparent, Color::Yellow);
	grSecond = new __interface_companents::gradient(FloatRect(Vector2f(150, 150), Vector2f(180, 5)), __interface_companents::gradient_direction::leftOnRight, Color::Transparent, Color::Yellow);

	delete t;
}

menu_settings::menu_settings(configuration* cf, const Font& font, const Color& maincl, const Color& bordercl) :
	active(false),
	blackout_visible(true)
{
	pos.x = cf->screenWidth / 2;
	pos.y = cf->screenHeight / 2;
	main = new RectangleShape;
	main->setSize(Vector2f(550, 600));
	main->setFillColor(maincl);
	main->setPosition(pos.x - main->getGlobalBounds().width / 2, pos.y - main->getGlobalBounds().height / 2);

	border = new RectangleShape;
	border->setSize(Vector2f(main->getGlobalBounds().width + 10, main->getGlobalBounds().height + 10));
	border->setFillColor(bordercl);
	border->setPosition(pos.x - 5 - main->getGlobalBounds().width / 2, pos.y - 5 - main->getGlobalBounds().height / 2);

	blackout = new RectangleShape;
	blackout->setSize(Vector2f(cf->screenWidth, cf->screenWidth));
	blackout->setFillColor(Color(0, 0, 0, 255 / 2));
	blackout->setPosition(0, 0);

	btBack = new __interface_companents::button((main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 410, font, L"Назад", Color::Black, Color::Yellow, Color::Yellow);
	btSave = new __interface_companents::button((main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 480, font, L"Сохранить", Color::Black, Color::Yellow, Color::Yellow);
	btBack->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (btBack->getSize().width / 2), main->getGlobalBounds().top + 410);
	btSave->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (btSave->getSize().width / 2), main->getGlobalBounds().top + 480);


	auto* t = new std::string(intToStr(std::string, cf->screenWidth));
	*t += " x ";
	*t += intToStr(std::string, cf->screenHeight);

	txVertS = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 20, L"Вертикальная синхронизация:", Color::Yellow, Color::Black);
	txVertS->visible_bevel = false;
	txFullS = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 80, L"На весь экран:", Color::Yellow, Color::Black);
	txFullS->visible_bevel = false;

	txAnisF = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 140, L"Анизотропная фильтрация:", Color::Yellow, Color::Black);
	txAnisF->visible_bevel = false;

	txScreen = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 200, L"Разрешение экрана:", Color::Yellow, Color::Black);
	txScreen->visible_bevel = false;
	txSound = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 260, L"Звук:", Color::Yellow, Color::Black);
	txSound->visible_bevel = false;
	txSoundV = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 320, L"Громкость звука:", Color::Yellow, Color::Black);
	txSoundV->visible_bevel = false;

	txVertS->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txVertS->getSize().width / 2), main->getGlobalBounds().top + 20);
	txFullS->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txFullS->getSize().width / 2), main->getGlobalBounds().top + 80);

	txAnisF->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txAnisF->getSize().width / 2), main->getGlobalBounds().top + 140);

	txScreen->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txScreen->getSize().width / 2) - 50, main->getGlobalBounds().top + 200);
	txSound->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txSound->getSize().width / 2), main->getGlobalBounds().top + 260);
	txSoundV->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txSoundV->getSize().width / 2) - 50, main->getGlobalBounds().top + 320);

	combAnisF = new __interface_companents::combo_box(txAnisF->getSize().left + txAnisF->getSize().width + 5, txAnisF->getSize().top, Color::Yellow, Color::Yellow);
	combAnisF->add(L"Выкл.", 0);
	combAnisF->add(L"2", 2);
	combAnisF->add(L"6", 6);
	combAnisF->add(L"8", 8);
	combAnisF->add(L"16", 16);

	combScreen = new __interface_companents::combo_box(txScreen->getSize().left + txScreen->getSize().width + 5, txScreen->getSize().top, Color::Yellow, Color::Yellow);
	combScreen->add(L"1280 x 720", 0);
	combScreen->add(L"1600 x 900", 1);
	combScreen->add(L"1600 x 1200", 2);
	combScreen->add(L"1920 x 1080", 3);
	combScreen->add(L"2560 x 1440", 4);

	combSoundV = new __interface_companents::combo_box(txSoundV->getSize().left + txSoundV->getSize().width + 5, txSoundV->getSize().top, Color::Yellow, Color::Yellow);
	combSoundV->add(L"0", 0);
	combSoundV->add(L"10", 10);
	combSoundV->add(L"20", 20);
	combSoundV->add(L"30", 30);
	combSoundV->add(L"40", 40);
	combSoundV->add(L"50", 50);
	combSoundV->add(L"60", 60);
	combSoundV->add(L"70", 70);
	combSoundV->add(L"80", 80);
	combSoundV->add(L"90", 90);
	combSoundV->add(L"100", 100);

	while (std::wstring(t->begin(), t->end()) != combScreen->getText()) {
		combScreen->back();
	}

	*t = intToStr(std::string, cf->soundVolume);

	while (std::wstring(t->begin(), t->end()) != combSoundV->getText()) {
		combSoundV->back();
	}

	while (cf->anisFilt != combAnisF->getValue()) {
		combAnisF->back();
	}

	cbVertS = new __interface_companents::check_box((main->getGlobalBounds().width / 2) + 0 + (txVertS->getSize().width / 2) + 5, main->getGlobalBounds().top + 20, Color::Black, Color::Yellow, Color::Yellow);
	cbVertS->isCheck = cf->verticalSync;
	cbFullS = new __interface_companents::check_box((main->getGlobalBounds().width / 2) + 0 + (txFullS->getSize().width / 2) + 5, main->getGlobalBounds().top + 80, Color::Black, Color::Yellow, Color::Yellow);
	cbFullS->isCheck = cf->fullScreen;
	cbSound = new __interface_companents::check_box((main->getGlobalBounds().width / 2) + 0 + (txVertS->getSize().width / 2) + 5, main->getGlobalBounds().top + 260, Color::Black, Color::Yellow, Color::Yellow);
	cbSound->isCheck = cf->sound;

	cbVertS->setPosition(txVertS->getSize().left + txVertS->getSize().width + 5, main->getGlobalBounds().top + 20);
	cbFullS->setPosition(txFullS->getSize().left + txFullS->getSize().width + 5, main->getGlobalBounds().top + 80);
	cbSound->setPosition(txSound->getSize().left + txSound->getSize().width + 5, main->getGlobalBounds().top + 260);

	txMenuSettings = new __interface_companents::text_box(font, (main->getGlobalBounds().width / 2) + 0, main->getGlobalBounds().top + 550, L"Настройки", Color::Yellow, Color::Black);
	txMenuSettings->visible_bevel = false;
	grFirst = new __interface_companents::gradient(FloatRect(Vector2f(100, 100), Vector2f(180, 5)), __interface_companents::gradient_direction::rightOnLeft, Color::Transparent, Color::Yellow);
	grSecond = new __interface_companents::gradient(FloatRect(Vector2f(150, 150), Vector2f(180, 5)), __interface_companents::gradient_direction::leftOnRight, Color::Transparent, Color::Yellow);
	txMenuSettings->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txMenuSettings->getSize().width / 2), main->getGlobalBounds().top + 550);
	grFirst->setPosition(txMenuSettings->getPosition().x - 5 - grFirst->getSize().width, txMenuSettings->getPosition().y + (txMenuSettings->getSize().height / 2) - (grSecond->getSize().height / 2));
	grSecond->setPosition(txMenuSettings->getPosition().x + 5 + txMenuSettings->getSize().width, txMenuSettings->getPosition().y + (txMenuSettings->getSize().height / 2) - (grSecond->getSize().height / 2));

	delete t;
}

menu_settings::~menu_settings() {
	delete main, border, blackout;
	delete btBack, btSave;
	delete txVertS, txFullS, txScreen, txSound, txSoundV, txAnisF;
	delete cbFullS, cbVertS, cbSound;
	delete txMenuSettings;
	delete grFirst, grSecond;
	delete combScreen, combSoundV, combAnisF;
}

void menu_settings::backSettings(configuration* cf) {
	cbFullS->isCheck = cf->fullScreen;
	cbVertS->isCheck = cf->verticalSync;
	cbSound->isCheck = cf->sound;

	std::string* t = new std::string(intToStr(std::string, cf->screenWidth));
	*t += " x ";
	*t += intToStr(std::string, cf->screenHeight);

	while (std::wstring(t->begin(), t->end()) != combScreen->getText()) {
		combScreen->back();
	}

	*t = intToStr(std::string, cf->soundVolume);

	while (std::wstring(t->begin(), t->end()) != combSoundV->getText()) {
		combSoundV->back();
	}

	while (cf->anisFilt != combAnisF->getValue()) {
		combAnisF->back();
	}

	delete t;
}

int menu_settings::saveSettings(configuration* cf) {

	int H = 0, W = 0;

	switch (combScreen->getValue()) {
		case 0: W = 1280; H = 720; break;
		case 1: W = 1600; H = 900; break;
		case 2: W = 1600; H = 1200; break;
		case 3: W = 1920; H = 1080; break;
		case 4: W = 2560; H = 1440; break;
		default: break;
	}


	if (cf->fullScreen != cbFullS->isCheck || (cf->screenWidth != W && cf->screenHeight != H) || cf->anisFilt != combAnisF->getValue()) {
		cf->fullScreen = cbFullS->isCheck;
		cf->verticalSync = cbVertS->isCheck;
		cf->sound = cbSound->isCheck;
		cf->soundVolume = combSoundV->getValue();
		cf->screenWidth = W;
		cf->screenHeight = H;
		cf->anisFilt = combAnisF->getValue();
		cf->saveSettings();
		return static_cast<int>(settings_save_code::other);
	} else {
		cf->verticalSync = cbVertS->isCheck;
		cf->sound = cbSound->isCheck;
		cf->soundVolume = combSoundV->getValue();
		cf->saveSettings();
		return static_cast<int>(settings_save_code::sound_or_sound_volume_or_verticalS);
	}
}

void menu_settings::render(RenderWindow& wd, Camera* camera) noexcept {
	if (active) {
		pos = camera->getPosition();

		main->setPosition(pos.x - main->getGlobalBounds().width / 2, pos.y - main->getGlobalBounds().height / 2);
		border->setPosition(pos.x - 5 - main->getGlobalBounds().width / 2, pos.y - 5 - main->getGlobalBounds().height / 2);
		txVertS->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txVertS->getSize().width / 2), main->getGlobalBounds().top + 20);
		txFullS->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txFullS->getSize().width / 2), main->getGlobalBounds().top + 80);

		txAnisF->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txAnisF->getSize().width / 2), main->getGlobalBounds().top + 140);

		txScreen->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txScreen->getSize().width / 2) - 50, main->getGlobalBounds().top + 200);

		txSound->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txSound->getSize().width / 2), main->getGlobalBounds().top + 260);
		txSoundV->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txSoundV->getSize().width / 2), main->getGlobalBounds().top + 320);
		combSoundV->setPosition(txSoundV->getSize().left + txSoundV->getSize().width + 5, txSoundV->getSize().top);
		cbSound->setPosition(txSound->getSize().left + txSound->getSize().width + 5, main->getGlobalBounds().top + 260);

		combAnisF->setPosition(txAnisF->getSize().left + txAnisF->getSize().width + 5, txAnisF->getSize().top);

		combScreen->setPosition(txScreen->getSize().left + txScreen->getSize().width + 5, txScreen->getSize().top);
		btBack->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (btBack->getSize().width / 2), main->getGlobalBounds().top + 410);
		btSave->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (btSave->getSize().width / 2), main->getGlobalBounds().top + 480);
		cbVertS->setPosition(txVertS->getSize().left + txVertS->getSize().width + 5, main->getGlobalBounds().top + 20);
		cbFullS->setPosition(txFullS->getSize().left + txFullS->getSize().width + 5, main->getGlobalBounds().top + 80);
		txMenuSettings->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txMenuSettings->getSize().width / 2), main->getGlobalBounds().top + 550);
		grFirst->setPosition(txMenuSettings->getPosition().x - 5 - grFirst->getSize().width, txMenuSettings->getPosition().y + (txMenuSettings->getSize().height / 2) - (grSecond->getSize().height / 2));
		grSecond->setPosition(txMenuSettings->getPosition().x + 5 + txMenuSettings->getSize().width, txMenuSettings->getPosition().y + (txMenuSettings->getSize().height / 2) - (grSecond->getSize().height / 2));

		if (blackout_visible) {
			blackout->setPosition(camera->getPosition().x - (camera->getScreenWidth() / 2), camera->getPosition().y - (camera->getScreenHeight() / 2));
			wd.draw(*blackout);
		}
		wd.draw(*border);
		wd.draw(*main);

		txVertS->render(wd);
		txScreen->render(wd);
		txAnisF->render(wd);
		txFullS->render(wd);
		txSound->render(wd);
		txSoundV->render(wd);

		combAnisF->render(wd);
		combScreen->render(wd);
		combSoundV->render(wd);

		cbVertS->render(wd);
		cbFullS->render(wd);
		cbSound->render(wd);

		btBack->render(wd);
		btSave->render(wd);

		txMenuSettings->render(wd);
		grFirst->render(wd);
		grSecond->render(wd);
	}
}

void menu_settings::render(RenderWindow& wd) noexcept {
	if (active) {
		if (blackout_visible) {
			wd.draw(*blackout);
		}
		wd.draw(*border);
		wd.draw(*main);

		txVertS->render(wd);
		txScreen->render(wd);
		txAnisF->render(wd);
		txFullS->render(wd);
		txSound->render(wd);
		txSoundV->render(wd);

		combAnisF->render(wd);
		combScreen->render(wd);
		combSoundV->render(wd);

		cbVertS->render(wd);
		cbFullS->render(wd);
		cbSound->render(wd);

		btBack->render(wd);
		btSave->render(wd);

		txMenuSettings->render(wd);
		grFirst->render(wd);
		grSecond->render(wd);
	}
}
//------------------------Меню-настроек-menu_settings-Конец---------------------------------------