#include "World.hpp"

//-----------------------------------Мир-World-Начало-------------------------------------
World::World(Image* ptr_on_img, int X_SIZE, int Y_SIZE) :
	size_x(X_SIZE),
	size_y(Y_SIZE)
{
	worldTexture = new Texture;
	worldTexture->loadFromImage(*ptr_on_img);
	worldSpr = new Sprite;
	worldSpr->setTexture(*worldTexture);
	mass_sp = new sf::String[size_y];
	char* mass_ch = new char[size_x];

	for (int i = 0; i < size_x; i++) {
		mass_ch[i] = '0';
	}

	for (int i = 0; i < size_y; i++) {
		mass_sp[i] = sf::String(mass_ch);
	}
	delete[] mass_ch;
}

World::~World() noexcept {
	delete[] mass_sp;
	delete worldTexture, worldSpr;
}

void World::render(RenderWindow& wd) noexcept {
	for (int i = 0; i < size_y; i++) { //Отрисовка мира
		for (int j = 0; j < size_x; j++) {
			if (mass_sp[i][j] == '0') {
				worldSpr->setTextureRect(IntRect(0, 0, worldTexture->getSize().x, worldTexture->getSize().y)); //0, 0, 128, 128
			}
			worldSpr->setPosition(j * worldTexture->getSize().x, i * worldTexture->getSize().y);
			wd.draw(*worldSpr);
		}
	}
}
//-----------------------------------Мир-World-Конец-------------------------------------