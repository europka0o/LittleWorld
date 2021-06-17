#include "Message.hpp"

//-----------------------------Сообщение-message-Начало---------------------------------------
__interface_companents::message::message(int x, int y, const Font& font, const wchar_t* txt, const Color& maincl, const Color& bordercl, const Color& textcl) :
	active(false)
{
	pos.x = x;
	pos.y = y;

	main = new RectangleShape;
	//main_cl = new Color;
	//*main_cl = maincl;
	main->setFillColor(maincl);

	border = new RectangleShape;
	//border_cl = new Color;
	//*border_cl = bordercl;
	border->setFillColor(bordercl);

	txInfo = new text_box(font, 0, 0, txt, textcl);
	txInfo->visible_bevel = false;
	txMess = new text_box(font, 0, 0, L"Сообщение", Color::Yellow);
	txMess->visible_bevel = false;

	main->setSize(Vector2f(txInfo->getSize().width + 10, 150));
	border->setSize(Vector2f(main->getGlobalBounds().width + 10, main->getGlobalBounds().height + 10));

	main->setPosition(pos.x - main->getGlobalBounds().width / 2, pos.y - main->getGlobalBounds().height / 2);
	border->setPosition(main->getGlobalBounds().left - 5, main->getGlobalBounds().top - 5);

	txInfo->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txInfo->getSize().width / 2), main->getGlobalBounds().top + 10);
	txMess->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txMess->getSize().width / 2), main->getGlobalBounds().top + main->getGlobalBounds().height - 50);
	grFirst = new gradient(FloatRect(Vector2f(0, 0), Vector2f(150, 5)), gradient_direction::rightOnLeft, Color::Transparent, Color::Yellow);
	grSecond = new gradient(FloatRect(Vector2f(0, 0), Vector2f(150, 5)), gradient_direction::leftOnRight, Color::Transparent, Color::Yellow);

	grFirst->setPosition(txMess->getPosition().x - 5 - grFirst->getSize().width, txMess->getPosition().y + (txMess->getSize().height / 2) - (grFirst->getSize().height / 2));
	grSecond->setPosition(txMess->getPosition().x + 5 + txMess->getSize().width, txMess->getPosition().y + (txMess->getSize().height / 2) - (grSecond->getSize().height / 2));

	btOk = new button(0, 0, font, L"Ок", Color::Black, Color::Yellow, Color::Yellow);
	btOk->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (btOk->getSize().width / 2), txMess->getSize().top - 35);
}

__interface_companents::message::~message() {
	delete main, border;
	delete txInfo, txMess;
	delete grFirst, grSecond;
	delete btOk;
}

void __interface_companents::message::render(RenderWindow& wd, Camera* camera) noexcept {
	if (active) {
		pos = camera->getPosition();

		main->setPosition(pos.x - main->getGlobalBounds().width / 2, pos.y - main->getGlobalBounds().height / 2);
		border->setPosition(pos.x - 5 - main->getGlobalBounds().width / 2, pos.y - 5 - main->getGlobalBounds().height / 2);
		txInfo->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txInfo->getSize().width / 2), main->getGlobalBounds().top + 10);
		txMess->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (txMess->getSize().width / 2), main->getGlobalBounds().top + main->getGlobalBounds().height - 50);
		btOk->setPosition(main->getGlobalBounds().left + (main->getGlobalBounds().width / 2) - (btOk->getSize().width / 2), txInfo->getSize().top + txInfo->getSize().height + 20);
		grFirst->setPosition(txMess->getPosition().x - 5 - grFirst->getSize().width, txMess->getPosition().y + (txMess->getSize().height / 2) - (grSecond->getSize().height / 2));
		grSecond->setPosition(txMess->getPosition().x + 5 + txMess->getSize().width, txMess->getPosition().y + (txMess->getSize().height / 2) - (grSecond->getSize().height / 2));

		wd.draw(*border);
		wd.draw(*main);

		txInfo->render(wd);

		btOk->render(wd);

		txMess->render(wd);
		grFirst->render(wd);
		grSecond->render(wd);
	}
}

void __interface_companents::message::render(RenderWindow& wd) noexcept {
	if (active) {
		wd.draw(*border);
		wd.draw(*main);

		txInfo->render(wd);
		btOk->render(wd);

		txMess->render(wd);
		grFirst->render(wd);
		grSecond->render(wd);
	}
}
//-----------------------------Сообщение-message-Конец---------------------------------------