#include "BackgroundColor.hpp"
#include "Bar.hpp"
#include "Camera.hpp"
#include "DestroerCastle.hpp"
#include "Spearman.hpp"
#include "IceBall.hpp"
#include "Knight.hpp"
#include "Meteor.hpp"
#include "Message.hpp"
#include "MainMenu.hpp"
#include "MenuPause.hpp"
#include "MenuSettings.hpp"
#include "World.hpp"
#include "MultilineText.hpp"
#include "MemoryPool.hpp"

#include <iostream>
#include <SFML/Audio.hpp>
#include <list>
#include <random>
#pragma once

enum lvlnum {
	lvlRun = 1,
	lvlTraining,
	menuGame,
	exitGame = 0
};

class Game {
	private:
		configuration *config;
		RenderWindow *window;

		uint32_t block_memory_sprite;
		uint32_t block_memory_font;
		uint32_t block_memory_texture;

		void* ptr_global_memory;

		sf::Vector2i pos;
		sf::Vector2f realPos;
		uint32_t CENTER_SCREEN_X;
		uint32_t CENTER_SCREEN_Y;
		int volume; //Громкость звука
		float barhp; //Здоровье
		float barmp; //Текущее значение маны
		float barmp_max; //Максимальное значение маны, нужно для восстановления маны
		int mp_need_cast_expl; //Нужное кол-во маны для взрыва
		int mp_need_cast_ice; //Нужное кол-во маны для призыва кристалла
		
	public:
		Game();
		~Game();
		int Run();
		int LvlRun();
		int lvlTraining();
		void ExecuteCommand(const char* command);
		void StartApp();
};