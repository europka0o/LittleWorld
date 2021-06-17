#if defined _WIN32 || defined _WIN64 //��� windows

#include <windows.h>

unsigned int screen_width = GetSystemMetrics(SM_CXSCREEN);
unsigned int screen_height = GetSystemMetrics(SM_CYSCREEN);

#endif
#include "Game.hpp"

Game::Game() {
	
	config = new configuration;
	if (!config->loadSettings()) {
		config->createSettings(screen_width, screen_height, 8, true, 30, true, true, 50);
	}

	if (config->sound) {
		volume = config->soundVolume;
	} else {
		volume = 0;
	}

	sf::ContextSettings settings_sf;
	settings_sf.antialiasingLevel = config->anisFilt;

	window = new RenderWindow(VideoMode(config->screenWidth, config->screenHeight), "Little World", config->fullScreen ? 8 : 7, settings_sf);
	window->setVerticalSyncEnabled(config->verticalSync);

	ptr_global_memory = memory_block_allocation_void(sizeof(Image) + (sizeof(Texture) * 11) + (sizeof(Sprite) * 11) + sizeof(Font));

	block_memory_texture = sizeof(Image);
	block_memory_sprite = block_memory_texture + (sizeof(Texture) * 11);
	block_memory_font = block_memory_sprite + (sizeof(Sprite) * 11);

	memory_initialization(pointer_cast(ptr_global_memory, Image), Image);

	for (int i = 0; i < 11; i++) {
		memory_initialization(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + i, Texture);
		memory_initialization(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + i, Sprite);
	}

	memory_initialization(pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), Font);

	(pointer_cast(ptr_global_memory, Image))->loadFromFile("Img/ground.png");

	(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + 0)->loadFromFile("Img/exp.png");
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + 1)->loadFromFile("Img/meteor.png");
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + 2)->loadFromFile("Img/castle.png");
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + 3)->loadFromFile("Img/sprman.png");
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + 4)->loadFromFile("Img/CastlDestr.png");
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + 5)->loadFromFile("Img/gg.png");
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + 6)->loadFromFile("Img/ice.png");
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + 7)->loadFromFile("Img/World.png");
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + 8)->loadFromFile("Img/castd.png");
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + 9)->loadFromFile("Img/d1.png");
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + 10)->loadFromFile("Img/castd2.png");

	for (int i = 0; i < 11; i++) {
		(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + i)->setTexture(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + i));
	}

	pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font)->loadFromFile("Img/18094.ttf");

	(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 7)->setOrigin((pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 7)->getGlobalBounds().width / 2.f,
																								(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 7)->getGlobalBounds().height / 2.f);
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 7)->setPosition((config->screenWidth / 2 + 100), config->screenHeight / 2);

	(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 8)->setOrigin(((pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 8)->getGlobalBounds().width / 2) + 30,
																								(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 7)->getOrigin().y + 137);
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 8)->setPosition((config->screenWidth / 2 + 100), config->screenHeight / 2);

	(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 10)->setOrigin(((pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 10)->getGlobalBounds().width / 2) + 30,
																								(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 7)->getOrigin().y + 137);
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 10)->setPosition((config->screenWidth / 2 + 100), config->screenHeight / 2);

	(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 9)->setOrigin(((pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 9)->getGlobalBounds().width / 2) - 20,
																								(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 7)->getOrigin().y + 110);
	(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 9)->setPosition((config->screenWidth / 2 + 100), config->screenHeight / 2);

	CENTER_SCREEN_X = config->screenWidth / 2;
	CENTER_SCREEN_Y = config->screenHeight / 2;

	barhp = 200; 
	barmp_max = 150;
	barmp = barmp_max;
	mp_need_cast_expl = 20;
	mp_need_cast_ice = 100; 

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Game::~Game() {
	delete config, window; 

	destructor(pointer_cast(ptr_global_memory, Image), Image);

	for (int i = 0; i < 11; i++) {
		destructor(pointer_cast(((char*)(ptr_global_memory) + block_memory_texture), Texture) + i, Texture);
		destructor(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + i, Sprite);
	}

	destructor(pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), Font);

	free_block_memory(ptr_global_memory);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Game::Run() {
	Clock clock;
	float timer = 0;

	main_menu *main_men = new main_menu(config, r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), Color(38, 38, 38, 255));
	menu_settings *st_men = new menu_settings(config, r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), Color::Color(38, 38, 38, 255), Color::Yellow);
	st_men->blackout_visible = true;

	__interface_companents::message *message_settings = new __interface_companents::message(config->screenWidth / 2, config->screenHeight / 2, r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), L"��������� ������� � ���� ����� ����������� ����", Color(38, 38, 38, 255), Color::Yellow, Color::Yellow);

	auto random {
		[](__int32 _from, __int32 _do)->__int32 {
			std::random_device rd;
			std::mt19937_64 gen(rd());
			std::uniform_int_distribution<int> dist(_from, _do);
			return dist(gen);
		}
	};

	int rand_i = random(8, 9);

	if (rand_i == 8) {
		(pointer_cast(((char*)(ptr_global_memory)+block_memory_sprite), Sprite) + rand_i)->setRotation((pointer_cast(((char*)(ptr_global_memory)+block_memory_sprite), Sprite) + 9)->getRotation() + 100);
	} else {
		rand_i = 10;
		(pointer_cast(((char*)(ptr_global_memory)+block_memory_sprite), Sprite) + rand_i)->setRotation((pointer_cast(((char*)(ptr_global_memory)+block_memory_sprite), Sprite) + 9)->getRotation() - 100);
	}

	while (window->isOpen()) {

		timer = clock.getElapsedTime().asMicroseconds();
		timer /= 1000;

		pos = sf::Mouse::getPosition(*window);
		realPos = window->mapPixelToCoords(pos);
		Event event;

		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
			}

			if (!st_men->active && !message_settings->active) {
				if (main_men->btExit->isAction(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						window->close();
					}
				}

				if (main_men->btStart->isAction(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						delete main_men, st_men, message_settings;
						return lvlnum::lvlRun;
					}
				}

				if (main_men->btStartTren->isAction(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						delete main_men, st_men, message_settings;
						return lvlnum::lvlTraining;
					}
				}

				if (main_men->btOptions->isAction(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						st_men->active = true;
					}
				}

			} else if (!message_settings->active) {
				if (st_men->btBack->isAction(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						st_men->active = false;
						st_men->backSettings(config);
					}
				}

				if (st_men->cbFullS->getSize().contains(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						st_men->cbFullS->invers();
					}
				}

				if (st_men->cbVertS->getSize().contains(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						st_men->cbVertS->invers();
					}
				}

				if (st_men->cbSound->getSize().contains(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						st_men->cbSound->invers();
					}
				}

				if (st_men->btSave->isAction(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						if (st_men->saveSettings(config) == static_cast<int>(settings_save_code::other)) {
							message_settings->active = true;
						} else {
							st_men->active = false;
						}

						window->setVerticalSyncEnabled(config->verticalSync);

						if (config->sound) {
							volume = config->soundVolume;
						} else {
							volume = 0;
						}
					}
				}

				if (st_men->combAnisF->isAction(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						st_men->combAnisF->next();
					} else if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right) {
						st_men->combAnisF->back();
					}
				}

				if (st_men->combScreen->isAction(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						st_men->combScreen->next();
					} else if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right) {
						st_men->combScreen->back();
					}
				}

				if (st_men->combSoundV->isAction(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						st_men->combSoundV->next();
					} else if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right) {
						st_men->combSoundV->back();
					}
				}

			} else {
				if (message_settings->btOk->isAction(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						message_settings->active = false;
						st_men->active = false;
					}
				}
			}
		}

		(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 7)->rotate(0.01 * timer / 16); //Planet->sprt->rotate(0.01);
		(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + rand_i)->rotate(0.17 * timer / 16); //D1->sprt->rotate(0.17);
		(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 9)->rotate(0.17 * timer / 16); //Castd->sprt->rotate(0.17);
		clock.restart();

		window->clear();
		main_men->render(*window);
		window->draw(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + rand_i));
		window->draw(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 9));
		window->draw(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 7));
		st_men->render(*window);
		message_settings->render(*window);
		window->display();
	}
			
	delete main_men, st_men, message_settings;
	return lvlnum::exitGame;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Game::LvlRun() {
	using std::list;

	Clock clock;
	World *MainWrd;
	__interface_companents::bar *HP;
	__interface_companents::bar *MP;
	__interface_companents::multiline_text *mlt;
	__interface_companents::text_box *lvlInfo;
	Camera *CameraMain;

	ObjectStatic *Castle;
	menu_pause *men;
	list<Meteor*> *Expl_list = new list<Meteor*>;

	Sprite* pointer_sprt = nullptr;

	list<BaseCharacter*> *EnemyList = new list<BaseCharacter*>;
	list<IceBall*> *IceList = new list<IceBall*>;

	MainWrd = new World((pointer_cast(ptr_global_memory, Image)), 40, 60);
	mlt = new __interface_companents::multiline_text(100, 200, Color::Black, Color::Yellow);
	mlt->resize(__interface_companents::text_size::normal);
	CameraMain = new Camera(CENTER_SCREEN_X, CENTER_SCREEN_Y, config->screenWidth, config->screenHeight);

	Castle = new ObjectStatic(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 2), 0, 0); //�����
	Castle->sprite_rect = IntRect(0, 0, 400, 1500);
	Castle->rect_collis->setBounds(IntRect(0, 0, 400, 1500));
	int numlvl = 0; //����� �����
	bool change_numlvl = false; //����� �����
	bool cooldown_expl = false; //������� ��� ���������

	float timer; //���������� �����

	HP = new __interface_companents::bar(r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), 5, 5, barhp, 0, L"HP:", Color::White, Color::Red, Color::Black); //������ ��������
	MP = new __interface_companents::bar(r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), 5, HP->getSize().left + HP->getSize().width + 5, barmp_max, 0, L"MP:", Color::White, Color::Blue, Color::Black); //������ ����

	__interface_companents::message *message_end = new __interface_companents::message(config->screenWidth / 2, config->screenHeight / 2, r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), L"���������� ��������� ��� �����, �� ���������", Color(38, 38, 38, 255), Color::Yellow, Color::Yellow);
	__interface_companents::message *message_vic = new __interface_companents::message(config->screenWidth / 2, config->screenHeight / 2, r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), L"�� �������� ���� ���������� �����������! �����������!", Color(38, 38, 38, 255), Color::Yellow, Color::Yellow);
	__interface_companents::message *message_settings = new __interface_companents::message(config->screenWidth / 2, config->screenHeight / 2, r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), L"��������� ������� � ���� ����� ����������� ����", Color(38, 38, 38, 255), Color::Yellow, Color::Yellow);

	menu_settings *st_men = new menu_settings(config, r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), Color::Color(38, 38, 38, 255), Color::Yellow); //���� ��������
	men = new menu_pause(CameraMain, r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), Color::Color(38, 38, 38, 255), Color::Yellow); //������� ����
	men->active = false;
	st_men->blackout_visible = false;
			
	lvlInfo = new __interface_companents::text_box(r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), 0, 0, L"����� 1", Color::Black, Color::Yellow); //������� � ������� �����
	lvlInfo->resize(__interface_companents::text_size::medium);
	lvlInfo->setPosition((config->screenWidth / 2) - lvlInfo->getSize().width / 2, (config->screenHeight / 2) - lvlInfo->getSize().height / 2);
			

	mlt->add(L"�������!");
	mlt->add(L"�� ��� ����� ��������");

	float Second = 0; //����������� ����� � ��������
	float NacopSec = 0; //����������� ����� � ��������
	float NacopSec2 = 0; //����������� ����� � ��������

//------------------------------------------------------------------------------------------------------------------------����� � ������
	SoundBuffer shootBuffer; //������ ����� ��� �����																		
	shootBuffer.loadFromFile("Sounds/expls.ogg"); //��������� � ���� ����													
	Sound expl_sound(shootBuffer); //������� ���� � ��������� � ���� ���� �� ������												
			
	expl_sound.setVolume(volume);

	SoundBuffer game_overBuffer;
	game_overBuffer.loadFromFile("Sounds/game_over.ogg");
	Sound game_over_sound(game_overBuffer);

	game_over_sound.setVolume(volume);

	SoundBuffer victoryBuffer;
	victoryBuffer.loadFromFile("Sounds/victory.ogg");
	Sound victory_sound(victoryBuffer);

	victory_sound.setVolume(volume);

	SoundBuffer attackBuffer;
	attackBuffer.loadFromFile("Sounds/attack.ogg");
	list<Sound*> *attack_sound = new list<Sound*>;
			
	SoundBuffer attackIceBuffer;
	attackIceBuffer.loadFromFile("Sounds/attack_ice.ogg");
	list<Sound*> *attack_ice_sound = new list<Sound*>;
		
	Music *music_main_theme = new Music; //������� ������ ������																
	music_main_theme->openFromFile("Sounds/main_theme.ogg"); //��������� ����		
	music_main_theme->setVolume(volume);
	music_main_theme->play();

	auto free_memory_list {
		[Expl_list, EnemyList, IceList,
			men, st_men,
			HP, MP, 
			mlt, lvlInfo, 
			attack_ice_sound, attack_sound, music_main_theme,
			MainWrd, CameraMain,
			message_settings, message_end, message_vic]()->void {
			for (list<Meteor*>::iterator it_expl = Expl_list->begin(); it_expl != Expl_list->end();) {
				delete* it_expl;
				it_expl = Expl_list->erase(it_expl);
			}
			delete Expl_list;
			delete men, st_men;
			delete HP, MP;
			delete mlt;
			delete lvlInfo;
			for (list<Sound*>::iterator it_sd_ice = attack_ice_sound->begin(); it_sd_ice != attack_ice_sound->end();) {
				delete* it_sd_ice;
				it_sd_ice = attack_ice_sound->erase(it_sd_ice);
			}
			for (list<Sound*>::iterator it_sd = attack_sound->begin(); it_sd != attack_sound->end();) {
				delete* it_sd;
				it_sd = attack_sound->erase(it_sd);
			}
			for (list<BaseCharacter*>::iterator it_en = EnemyList->begin(); it_en != EnemyList->end();) {
				delete* it_en;
				it_en = EnemyList->erase(it_en);
			}
			for (list<IceBall*>::iterator it_ic = IceList->begin(); it_ic != IceList->end();) {
				delete* it_ic;
				it_ic = IceList->erase(it_ic);
			}
			delete EnemyList, IceList;
			delete MainWrd;
			delete message_settings, message_end, message_vic;
			delete CameraMain;
			delete music_main_theme, attack_sound, attack_ice_sound;
		}
	};

//------------------------------------------------------------------------------------------------------------------------------------
			
	while (window->isOpen()) {
				
		music_main_theme->setLoop(true);

		timer = clock.getElapsedTime().asMicroseconds(); //�������� ����� � ��������
		Second = clock.getElapsedTime().asSeconds(); //�������� ����� � ��������
		clock.restart();
		timer /= 1000;
		//timer -= 10;
		pos = sf::Mouse::getPosition(*window);
		realPos = window->mapPixelToCoords(pos);
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
			}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------���� � ��� ����������� �������
			if (!message_end->active && !message_vic->active) {
				if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && !men->active) { //���� ������ ����� ������ ����
					if (barmp >= mp_need_cast_expl) {
						Expl_list->push_back(new Meteor(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 0), realPos.x - 200, realPos.y - 200));
						barmp -= mp_need_cast_expl;
					}
				}

				if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right && !men->active) { //���� ������ ������ ������ ����
					if (barmp >= mp_need_cast_ice) {
						if (IceList->empty()) {
							IceList->push_back(new IceBall(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 6), realPos.x - 55, realPos.y - 65, 200));
						} else {
							IceList->back()->health = 0;
							IceList->push_back(new IceBall(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 6), realPos.x - 55, realPos.y - 65, 200));
						}
						barmp -= mp_need_cast_ice;
					}
				}

				if (men->active && !st_men->active) { //���� �����
					if (men->btContinue->isAction(realPos.x, realPos.y)) { //���� ������ ������ ���������� 
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							men->active = false;
						}
					}

					if (men->btOptions->isAction(realPos.x, realPos.y)) { //���� ������ ������ ���������
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->active = true;
						}
					}

					if (men->btExit->isAction(realPos.x, realPos.y)) { //���� ������ ������ �����
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							free_memory_list();
							return lvlnum::menuGame;
						}
					}
				} else if (st_men->active && !message_settings->active) { //���� ��������
					if (st_men->btBack->isAction(realPos.x, realPos.y)) { //���� ������ ������ �����
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->active = false;
							st_men->backSettings(config);
						}
					}

					if (st_men->cbFullS->getSize().contains(realPos.x, realPos.y)) { //���� ����� ������� �� ���� �����
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->cbFullS->invers();
						}
					}

					if (st_men->cbVertS->getSize().contains(realPos.x, realPos.y)) { //���� ����� ������� ����������� �������������
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->cbVertS->invers();
						}
					}

					if (st_men->cbSound->getSize().contains(realPos.x, realPos.y)) { //���� ����� ������� �����
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->cbSound->invers();
						}
					}

					if (st_men->btSave->isAction(realPos.x, realPos.y)) { //���� ������ ������ ���������
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							if (st_men->saveSettings(config) == static_cast<int>(settings_save_code::other)) {
								message_settings->active = true;
							} else {
								st_men->active = false;
							}	

							window->setVerticalSyncEnabled(config->verticalSync);

							if (config->sound) {
								volume = config->soundVolume;
							} else {
								volume = 0;
							}
							music_main_theme->setVolume(volume);
						}
					}

					if (st_men->combAnisF->isAction(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->combAnisF->next();
						} else if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right) {
							st_men->combAnisF->back();
						}
					}

					if (st_men->combScreen->isAction(realPos.x, realPos.y)) { 
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) { //���� ������ ����� ������ ���� �� ���������� ���������� ������
							st_men->combScreen->next();
						} else if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right) { //���� ������ ������ ������ ���� �� ���������� ���������� ������
							st_men->combScreen->back();
						}
					}
						
					if (st_men->combSoundV->isAction(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) { //���� ������ ����� ������ ���� �� ��������� �����
							st_men->combSoundV->next();
						} else if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right) { //���� ������ ������ ������ ���� �� ��������� �����
							st_men->combSoundV->back();
						}
					}

				} else {
					if (message_settings->btOk->isAction(realPos.x, realPos.y)) { //���� ������ ������ �� � ���������
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							message_settings->active = false;
							st_men->active = false;
						}
					}
				}
			} else {
				if (message_end->btOk->isAction(realPos.x, realPos.y) && message_end->active) { //���� ������ ������ �� � ��������� � ���������
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						free_memory_list();
						return lvlnum::menuGame;
					}
				}

				if (message_vic->btOk->isAction(realPos.x, realPos.y) && message_vic->active) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						free_memory_list();
						return lvlnum::menuGame;
					}
				}
			}

			if (window->isOpen()) { break; }
		}

		if (!message_end->active) {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { //�����
				men->active = true;
			}

			if (change_numlvl) {
				switch (numlvl) {
				case 1: //������ �����
					lvlInfo->visible = false;
					lvlInfo->setString(L"����� 2");
					lvlInfo->resize(__interface_companents::text_size::medium);
					lvlInfo->setPosition((config->screenWidth / 2) - lvlInfo->getSize().width / 2, (config->screenHeight / 2) - lvlInfo->getSize().height / 2);

					if (config->screenWidth == 2560 && config->screenHeight == 1440) { //���� ���������� ������ 2560 � 1440

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 500, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 600, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10, 700, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 900, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 1000, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140, 1100, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 900, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 920, 230, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 905, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 900, 560, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 980, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 950, 920, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 740, 990, 45));
					} else if (config->screenWidth == 1280 && config->screenHeight == 720) { //���� ���������� 1280 � 720
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 900, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 920, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 905, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 900, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 980, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 950, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 740, 400, 45));
					} else { //���� ����� ������
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 180, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 260, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 340, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10, 420, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 500, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 580, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 660, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140, 740, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 900, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 920, 190, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 905, 280, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 900, 370, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 980, 460, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 950, 550, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 740, 640, 45));
					}

					change_numlvl = false;
					break;
				case 2: //������ �����
					lvlInfo->visible = false;
					lvlInfo->setString(L"����� 3");
					lvlInfo->resize(__interface_companents::text_size::medium);
					lvlInfo->setPosition((config->screenWidth / 2) - lvlInfo->getSize().width / 2, (config->screenHeight / 2) - lvlInfo->getSize().height / 2);

					mp_need_cast_expl -= 4; //mp_need_cast_expl = 16

					if (config->screenWidth == 2560 && config->screenHeight == 1440) { //���� ���������� ������ 2560 � 1440

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 200, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 29, 230, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 114, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 27, 560, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 55, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 240, 920, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 990, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 300, 1200, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 980, 230, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 995, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 990, 560, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 920, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 970, 990, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1040, 100, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 230, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 560, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1908, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 920, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 560, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1910, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 920, 45));
					} else if (config->screenWidth == 1280 && config->screenHeight == 720) { //���� ���������� 1280 � 720
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 200, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 29, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 114, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 27, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 55, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 240, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 300, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 980, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 995, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 990, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 970, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1040, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 20, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 70, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 120, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 170, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1908, 220, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 270, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 320, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 370, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1910, 420, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 470, 45));
					} else { //���� ����� ������
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 200, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 29, 180, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 114, 260, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 27, 340, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 55, 420, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 240, 500, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 580, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 300, 660, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 980, 180, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 995, 260, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 990, 340, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 420, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 500, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 970, 580, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1040, 660, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 170, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 240, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 310, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1908, 380, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 520, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 590, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1910, 660, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 730, 45));
					}

					change_numlvl = false;
					break;
				case 3: //������ �����
					lvlInfo->visible = false;
					lvlInfo->setString(L"����� 4");
					lvlInfo->resize(__interface_companents::text_size::medium);
					lvlInfo->setPosition((config->screenWidth / 2) - lvlInfo->getSize().width / 2, (config->screenHeight / 2) - lvlInfo->getSize().height / 2);

					mp_need_cast_expl -= 4; //mp_need_cast_expl = 12

					if (config->screenWidth == 2560 && config->screenHeight == 1440) { //���� ���������� ������ 2560 � 1440

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 500, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 600, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10, 700, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 900, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 1000, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140, 1100, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 980, 230, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 995, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 990, 560, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 920, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 970, 990, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1040, 1000, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 230, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 560, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1908, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 920, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 560, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1910, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 920, 45));
					} else if (config->screenWidth == 1280 && config->screenHeight == 720) { //���� ���������� 1280 � 720
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 980, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 995, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 990, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 970, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1040, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 90, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 130, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 170, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1908, 210, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 290, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 330, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1910, 370, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 410, 45));
					} else { //���� ����� ������
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140, 500, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 980, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 995, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 990, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 970, 500, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1040, 550, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1908, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1910, 550, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 600, 45));
					}

					change_numlvl = false;
					break;
				case 4: //��������� �����
					lvlInfo->visible = false;
					lvlInfo->setString(L"����� 5");
					lvlInfo->resize(__interface_companents::text_size::medium);
					lvlInfo->setPosition((config->screenWidth / 2) - lvlInfo->getSize().width / 2, (config->screenHeight / 2) - lvlInfo->getSize().height / 2);

					mp_need_cast_expl -= 2; //mp_need_cast_expl = 10

					if (config->screenWidth == 2560 && config->screenHeight == 1440) { //���� ���������� ������ 2560 � 1440

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 200, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 29, 230, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 114, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 27, 560, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 55, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 240, 920, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 990, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 300, 1200, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 120, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 980, 240, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 995, 410, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 990, 550, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 810, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 930, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 970, 970, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1040, 1100, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 110, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 220, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 405, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 575, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1908, 809, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 915, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1890, 970, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 2000, 1005, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1950, 1130, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 2100, 600, 650));
					} else if (config->screenWidth == 1280 && config->screenHeight == 720) { //���� ���������� 1280 � 720
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 200, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 29, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 114, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 27, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 55, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 240, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 300, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 980, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 995, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 990, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 970, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1040, 400, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 90, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 130, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 170, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1908, 210, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1890, 390, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 2000, 430, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1950, 450, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 2100, 400, 650));
					} else { //���� ����� ������
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 200, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 29, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 114, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 27, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 55, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 240, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 300, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 980, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 995, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 990, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 970, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1040, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1905, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1900, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1908, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1920, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1890, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 2000, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1950, 500, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 2100, 450, 650));
					}
		
					change_numlvl = false;
					break;
				case 5: //����� �����
					lvlInfo->visible = false;
					lvlInfo->setString(L"����� 6");
					lvlInfo->resize(__interface_companents::text_size::medium);
					lvlInfo->setPosition((config->screenWidth / 2) - lvlInfo->getSize().width / 2, (config->screenHeight / 2) - lvlInfo->getSize().height / 2);

					mp_need_cast_ice -= 15; //mp_need_cast_ice = 85

					if (config->screenWidth == 2560 && config->screenHeight == 1440) { //���� ���������� ������ 2560 � 1440
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 29, 230, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 114, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 57, 560, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 95, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140, 920, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 230, 990, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 1200, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 230, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 560, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 920, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 990, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 1000, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 600, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 750, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 900, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 1050, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 1200, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1900, 200, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1870, 700, 500));
					} else if (config->screenWidth == 1280 && config->screenHeight == 720) { //���� ���������� 1280 � 720
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 29, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 114, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 57, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 95, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 230, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 400, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 400, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 450, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1900, 200, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1870, 450, 500));
					} else { //���� ����� ������
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 29, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 114, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 57, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 95, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 230, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 600, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1300, 500, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1900, 200, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1870, 500, 500));
					}

					change_numlvl = false;
					break;
				case 6: //������ �����
					lvlInfo->visible = false;
					lvlInfo->setString(L"����� 7");
					lvlInfo->resize(__interface_companents::text_size::medium);
					lvlInfo->setPosition((config->screenWidth / 2) - lvlInfo->getSize().width / 2, (config->screenHeight / 2) - lvlInfo->getSize().height / 2);

					mp_need_cast_expl -= 1; //mp_need_cast_expl = 9
							
					if (config->screenWidth == 2560 && config->screenHeight == 1440) { //���� ���������� ������ 2560 � 1440
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 20, 200, 400));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1200, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1150, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1100, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 600, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 750, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1100, 900, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1150, 1050, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1200, 1200, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1500, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1550, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1650, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1700, 600, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1650, 750, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 900, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1550, 1050, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1500, 1200, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1900, 600, 500));
					} else if (config->screenWidth == 1280 && config->screenHeight == 720) { //���� ���������� 1280 � 720
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 20, 200, 400));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1200, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1150, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1100, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1100, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1150, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1200, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1500, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1550, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1650, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1700, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1650, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1550, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1200, 450, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1900, 300, 500));
					} else { //���� ����� ������
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 20, 200, 400));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1200, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1150, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1100, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1000, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1050, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1100, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1150, 500, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1200, 550, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1500, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1550, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1650, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1700, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1650, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1600, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1550, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 1500, 500, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1900, 400, 500));
					}

					change_numlvl = false;
					break;
				case 7: //������� �����
					lvlInfo->visible = false;
					lvlInfo->setString(L"����� 8");
					lvlInfo->resize(__interface_companents::text_size::medium);
					lvlInfo->setPosition((config->screenWidth / 2) - lvlInfo->getSize().width / 2, (config->screenHeight / 2) - lvlInfo->getSize().height / 2);

					mp_need_cast_ice -= 15; //mp_need_cast_ice = 70

					if (config->screenWidth == 2560 && config->screenHeight == 1440) { //���� ���������� ������ 2560 � 1440
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 120, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 115, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 110, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 600, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 750, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 110, 900, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 115, 1050, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 120, 1200, 45));

						EnemyList->push_back(new DestroerCastle(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 4), config->screenWidth + 1000, 700, 1000));
					} else if (config->screenWidth == 1280 && config->screenHeight == 720) { //���� ���������� 1280 � 720
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 120, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 115, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 110, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 110, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 115, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 120, 450, 45));

						EnemyList->push_back(new DestroerCastle(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 4), config->screenWidth + 1000, 250, 1000));
					} else { //���� ����� ������
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 120, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 115, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 110, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 110, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 115, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 120, 500, 45));

						EnemyList->push_back(new DestroerCastle(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 4), config->screenWidth + 1000, 400, 1000));
					}

					change_numlvl = false;
					break;
				case 8: //������� �����
					lvlInfo->visible = false;
					lvlInfo->setString(L"����� 9");
					lvlInfo->resize(__interface_companents::text_size::medium);
					lvlInfo->setPosition((config->screenWidth / 2) - lvlInfo->getSize().width / 2, (config->screenHeight / 2) - lvlInfo->getSize().height / 2);
							
					if (config->screenWidth == 2560 && config->screenHeight == 1440) { //���� ���������� ������ 2560 � 1440
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 650, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 850, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 305, 650, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 305, 850, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 305, 1050, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 300, 300, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 350, 600, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 700, 800, 500));
					} else if (config->screenWidth == 1280 && config->screenHeight == 720) { //���� ���������� 1280 � 720
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 300, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 305, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 305, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 305, 350, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 300, 200, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 350, 300, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 700, 400, 500));
					} else { //���� ����� ������
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 105, 550, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 305, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 305, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 305, 550, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 300, 100, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 350, 300, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 700, 500, 500));
					}

					change_numlvl = false;
					break;
				case 9: //������� �����
					lvlInfo->visible = false;
					lvlInfo->setString(L"��������� �����");
					lvlInfo->resize(__interface_companents::text_size::medium);
					lvlInfo->setPosition((config->screenWidth / 2) - lvlInfo->getSize().width / 2, (config->screenHeight / 2) - lvlInfo->getSize().height / 2);

					if (config->screenWidth == 2560 && config->screenHeight == 1440) { //���� ���������� ������ 2560 � 1440
						EnemyList->push_back(new DestroerCastle(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 4), config->screenWidth + 100, 700, 1000));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 500, 300, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 700, 500, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 570, 900, 500));
					} else if (config->screenWidth == 1280 && config->screenHeight == 720) { //���� ���������� 1280 � 720
						EnemyList->push_back(new DestroerCastle(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 4), config->screenWidth + 100, 200, 1000));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 500, 150, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 700, 200, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 570, 250, 500));
					} else { //���� ����� ������
						EnemyList->push_back(new DestroerCastle(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 4), config->screenWidth + 100, 300, 1000));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 500, 300, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 700, 400, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 570, 600, 500));
					}

					change_numlvl = false;
					break;
				case 10: //������� �����
					lvlInfo->visible = false;
					lvlInfo->setString(L"������!");
					lvlInfo->resize(__interface_companents::text_size::medium);
					lvlInfo->setPosition((config->screenWidth / 2) - lvlInfo->getSize().width / 2, (config->screenHeight / 2) - lvlInfo->getSize().height / 2);

					mp_need_cast_ice -= 15; //mp_need_cast_ice = 55
					mp_need_cast_expl -= 1; //mp_need_cast_expl = 8

					if (config->screenWidth == 2560 && config->screenHeight == 1440) { //���� ���������� ������ 2560 � 1440
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 500, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 600, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10, 700, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 900, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 1000, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140, 1100, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130 + 400, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100 + 400, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70 + 400, 500, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40 + 400, 600, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10 + 400, 700, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40 + 400, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70 + 400, 900, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100 + 400, 1000, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140 + 400, 1100, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130 + 800, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100 + 800, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70 + 800, 500, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40 + 800, 600, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10 + 800, 700, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40 + 800, 800, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70 + 800, 900, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100 + 800, 1000, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140 + 800, 1100, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1300, 300, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1400, 800, 500));

						EnemyList->push_back(new DestroerCastle(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 4), config->screenWidth + 2000, 100, 1000));
						EnemyList->push_back(new DestroerCastle(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 4), config->screenWidth + 2700, 700, 1000));
					} else if (config->screenWidth == 1280 && config->screenHeight == 720) { //���� ���������� 1280 � 720
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130 + 400, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100 + 400, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70 + 400, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40 + 400, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10 + 400, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40 + 400, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70 + 400, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100 + 400, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140 + 400, 450, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130 + 800, 50, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100 + 800, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70 + 800, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40 + 800, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10 + 800, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40 + 800, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70 + 800, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100 + 800, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140 + 800, 450, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1300, 100, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1400, 400, 500));

						EnemyList->push_back(new DestroerCastle(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 4), config->screenWidth + 2000, 50, 1000));
						EnemyList->push_back(new DestroerCastle(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 4), config->screenWidth + 2700, 300, 1000));
					} else { //���� ����� ������
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140, 500, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130 + 400, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100 + 400, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70 + 400, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40 + 400, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10 + 400, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40 + 400, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70 + 400, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100 + 400, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140 + 400, 500, 45));

						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 130 + 800, 100, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100 + 800, 150, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70 + 800, 200, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40 + 800, 250, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 10 + 800, 300, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 40 + 800, 350, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 70 + 800, 400, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 100 + 800, 450, 45));
						EnemyList->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 140 + 800, 500, 45));

						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1300, 300, 500));
						EnemyList->push_back(new Knight(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 5), config->screenWidth + 1400, 500, 500));

						EnemyList->push_back(new DestroerCastle(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 4), config->screenWidth + 2000, 100, 1000));
						EnemyList->push_back(new DestroerCastle(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 4), config->screenWidth + 2700, 560, 1000));
					}

					change_numlvl = false;
					break;
				default:
					lvlInfo->visible = false;
					message_vic->active = true;
					change_numlvl = false;
					break;
				}
			}

			if (EnemyList->empty()) { //���� ������ ���
				NacopSec2 += Second;
				lvlInfo->visible = true;
				if (NacopSec2 >= 3) { //����� 3 ������� ������� �� ��������� �����
					numlvl++;
					change_numlvl = true;
					barmp = barmp_max;
				}

				if (numlvl == 11) { //���� ��� ����� ��������, �� ������
					music_main_theme->stop();
					victory_sound.setVolume(volume);
					victory_sound.play();
					numlvl++;
				}
			} else {
				NacopSec2 = 0;
			}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------����������� ���������
			if (!men->active) {

				for (list<Meteor*>::iterator it_expl = Expl_list->begin(); it_expl != Expl_list->end();) { 

					cooldown_expl = false;
					if ((*it_expl)->end) {
						delete* it_expl;
						it_expl = Expl_list->erase(it_expl);
					} else {

						if ((*it_expl)->reached_point && !(*it_expl)->is_sound_play) {
							expl_sound.setVolume(volume);
							expl_sound.play();
							(*it_expl)->is_sound_play = true;
						}

						for (list<BaseCharacter*>::iterator it_en = EnemyList->begin(); it_en != EnemyList->end();) {
							if ((*it_expl)->rect_collis->getBounds().intersects((*it_en)->rect_collis->getBounds()) && !(*it_expl)->cooldown) {
								cooldown_expl = true;
								(*it_en)->health -= 25;
								if ((*it_en)->health <= 0) {
									(*it_en)->health = 0; 
								}
							}
							it_en++;
						}

						(*it_expl)->update(timer);

						if (cooldown_expl) {
							(*it_expl)->cooldown = true;
						}
						it_expl++;
					}
				}
				//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
				for (list<BaseCharacter*>::iterator it_en = EnemyList->begin(); it_en != EnemyList->end();) {
						
					bool is_attack = false;
					int factor_demage = 1;
					float factor_speed = 1;
							
					switch ((*it_en)->descendant_class) {
						case SPEARMAN_CLASS: factor_demage = 1; 
												factor_speed = 2; break;
						case KNIGHT_CLASS: factor_demage = 3;
											factor_speed = 3.5; break;
						case DESTROERCASTLE_CLASS: factor_demage = 7;
													factor_speed = 3.5; break;
						default: break;
					}

					if ((*it_en)->is_dead) {
						delete* it_en;
						it_en = EnemyList->erase(it_en);
					} else {

						if ((*it_en)->rect_collis->getBounds().intersects(Castle->rect_collis->getBounds()) && (*it_en)->health != 0) {
							(*it_en)->attack(timer / 2);
							if (!(*it_en)->isCooldown(Second)) {							
								barhp -= (3 * factor_demage);
								(*it_en)->cooldown = true;
								attack_sound->push_back(new Sound(attackBuffer));
								attack_sound->back()->setVolume(volume);
								attack_sound->back()->play();
							}
							is_attack = true;
						}
			
						for (list<IceBall*>::iterator it_ic = IceList->begin(); it_ic != IceList->end();) {
							if ((*it_ic)->rect_collis->getBounds().intersects((*it_en)->rect_collis->getBounds())) {

								(*it_en)->attack(timer / 2);
								if (!(*it_en)->isCooldown(Second)) {

									(*it_ic)->health -= (3 * factor_demage);
									(*it_en)->cooldown = true;
									attack_ice_sound->push_back(new Sound(attackIceBuffer));
									attack_ice_sound->back()->setVolume(volume);
									attack_ice_sound->back()->play();
								}
								is_attack = true;
							}	
							it_ic++;
						}

						if (!is_attack) {
							(*it_en)->move(timer / factor_speed, direcrion4::left);
						}			
						it_en++;
					}
				}
				//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				bool Ice_ball_is_cooldown = false;
				for (list<IceBall*>::iterator it_ic = IceList->begin(); it_ic != IceList->end();) {
					if ((*it_ic)->is_dead) {
						delete* it_ic;
						it_ic = IceList->erase(it_ic);
					} else {

						for (list<BaseCharacter*>::iterator it_en = EnemyList->begin(); it_en != EnemyList->end();) {
							if ((*it_ic)->rect_collis->getBounds().intersects((*it_en)->rect_collis->getBounds())) {
								if (!(*it_ic)->cooldown) {
									(*it_en)->health -= 5;
									Ice_ball_is_cooldown = true;
									//(*it_ic)->cooldown = true;
								}
							}
							it_en++;
						}

						if (Ice_ball_is_cooldown) {
							(*it_ic)->cooldown = true;
						}

						if (!(*it_ic)->isCooldown(Second)) {
							Ice_ball_is_cooldown = false;
							(*it_ic)->cooldown = false;
						}

						(*it_ic)->update(timer / 4.5);
						it_ic++;
					}
				}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------������ ��������� ������
				for (list<Sound*>::iterator it_sd = attack_sound->begin(); it_sd != attack_sound->end();) {
					if (!(*it_sd)->getStatus()) {
						delete* it_sd;
						it_sd = attack_sound->erase(it_sd);
					} else {
						it_sd++;
					}
				}

				if (NacopSec2 >= 3) {
					mlt->visible = false;
				}

				HP->changeBar(barhp);
				HP->freeze(CameraMain, 5, 5);
				if (barhp <= 125) {
					barmp += timer / 100;
					Castle->sprite_rect = IntRect(400, 0, 400, 1500);
				} if (barhp <= 75) {
					Castle->sprite_rect = IntRect(400 * 2, 0, 400, 1500);
				} if (barhp <= 0) {
					Castle->sprite_rect = IntRect(400 * 3, 0, 400, 1500);
					barhp = 0;
					music_main_theme->stop();
					game_over_sound.play();
					message_end->active = true;
				}
				barmp >= barmp_max ? barmp = barmp_max : barmp += timer / 100;
				MP->changeBar(barmp);
				MP->freeze(CameraMain, 5, 40);
			}
		}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------���������
				
		window->clear();
		MainWrd->render(*window);
		CameraMain->setView(*window);
		for (list<BaseCharacter*>::iterator it_en = EnemyList->begin(); it_en != EnemyList->end();) {

			switch ((*it_en)->descendant_class) {
				case SPEARMAN_CLASS: 
					pointer_sprt = (pointer_cast(((char*)(ptr_global_memory)+block_memory_sprite), Sprite) + 3); break;
				case KNIGHT_CLASS:
					pointer_sprt = (pointer_cast(((char*)(ptr_global_memory)+block_memory_sprite), Sprite) + 5); break;
				case DESTROERCASTLE_CLASS:
					pointer_sprt = (pointer_cast(((char*)(ptr_global_memory)+block_memory_sprite), Sprite) + 4); break;
				default: pointer_sprt = nullptr; break;
			}
			(*it_en)->render(*window, pointer_sprt);
			it_en++;
		}
				
		for (list<IceBall*>::iterator it_ic = IceList->begin(); it_ic != IceList->end();) {
			(*it_ic)->render(*window, (pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 6));
			it_ic++;
		}

		Castle->render(*window, (pointer_cast(((char*)(ptr_global_memory)+block_memory_sprite), Sprite) + 2));

		for (list<Meteor*>::iterator it_met = Expl_list->begin(); it_met != Expl_list->end();) {
			(*it_met)->render(*window, (pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 0), (pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 1));
			it_met++;
		}

				
		HP->render(*window);
		MP->render(*window);
		mlt->render(*window);
		lvlInfo->render(*window);
		men->render(*window, CameraMain);
		st_men->render(*window, CameraMain);
		message_settings->render(*window, CameraMain); //Camera
		message_end->render(*window, CameraMain); //Camera
		message_vic->render(*window, CameraMain);
		window->display();
	}
			
	free_memory_list();

	return lvlnum::exitGame;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Game::lvlTraining() {
	using std::list;

	Clock clock;
	World *MainWrd;
	__interface_companents::bar *HP;
	__interface_companents::bar *MP;
	Camera *CameraMain;
	bool EnemyActive = false;

	auto *backgroundcl = new background_color(0, 0, Color(0, 0, 0, 200), config);
	backgroundcl->visible = true;

	auto *mlt = new __interface_companents::multiline_text(700, 340, Color::Black, Color::Yellow);
	
	mlt->add(L"                           ����� ����������!");
	mlt->add(L"��� ������������� �������, ����� ��� ���������");
	mlt->add(L"� ������� �������� �������� � �������� ����.");
	mlt->add(L"���� �� ������ ��� ����������, �� ������� ENTER, � ����");
	mlt->add(L"������ ���������� ������� ����� ������ ����.");
	mlt->resize(__interface_companents::text_size::normal);

	auto *mltAboutHP = new __interface_companents::multiline_text(700, 340, Color::Black, Color::Yellow);
	mltAboutHP->add(L"HP - health points(� ����. ���� ��������)");
	mltAboutHP->add(L"���� �������� ���������� ���������� ����� ������,");
	mltAboutHP->add(L"����� ������ ���������� ������ �� �����, ��� �����");
	mltAboutHP->add(L"����� ��������, �, �������������, �� ����������.");
	mltAboutHP->add(L"���������� ����� �� ���������.");
	mltAboutHP->add(L"������� ����� ������ ���� ����� ����������");
	mltAboutHP->visible = false;
	mltAboutHP->resize(__interface_companents::text_size::normal);

	auto *mltAboutMP = new __interface_companents::multiline_text(700, 340, Color::Black, Color::Yellow);
	mltAboutMP->add(L"MP - mana points(� ����. ���� ����)");
	mltAboutMP->add(L"���� ����� ��� ���� ����� �� ����� ��������� ���������");
	mltAboutMP->add(L"�������������� ����������, ��������� ��������� �����������.");
	mltAboutMP->add(L"� ������� �� HP ���� ���� �� �������� �����������������.");
	mltAboutMP->add(L"���� ��������� ���� ������ �� �����, �� �� �������� �����������");
	mltAboutMP->add(L"��������� ����������, ���� ���� �� ������������� �� ������������");
	mltAboutMP->add(L"���������� ���������� �����.");
	mltAboutMP->add(L"������� ����� ������ ���� ����� ����������");
	mltAboutMP->visible = false;
	mltAboutMP->resize(__interface_companents::text_size::normal);

	auto *mltAboutEnemy = new __interface_companents::multiline_text(700, 340, Color::Black, Color::Yellow);
	mltAboutEnemy->add(L"� ��� � ��� ������ ���������!");
	mltAboutEnemy->add(L"��� ����������� ��������� ������ ������������ ��� ��������.");
	mltAboutEnemy->add(L"�������� ���������� ��� �� ���� ��� �� ��������� �� �����.");
	mltAboutEnemy->add(L"�������� ������ �� ���������� � ������� �� ����� ������ ����");
	mltAboutEnemy->visible = false;
	mltAboutEnemy->resize(__interface_companents::text_size::normal);

	auto *mltAboutIce = new __interface_companents::multiline_text(700, 340, Color::Black, Color::Yellow);
	mltAboutIce->add(L"                                    ������!");
	mltAboutIce->add(L"�� � ��������� ��� ����� ������ �������� �� ����������,");
	mltAboutIce->add(L"������� �� ������ ������ ���� � ����� ����� �� �����.");
	mltAboutIce->visible = false;
	mltAboutIce->resize(__interface_companents::text_size::normal);

	auto *mltAboutIce2 = new __interface_companents::multiline_text(700, 340, Color::Black, Color::Yellow);
	mltAboutIce2->add(L"��� ������� ��������");
	mltAboutIce2->add(L"�� ����� ��������� ���� �����������, ���������� ������� ������,");
	mltAboutIce2->add(L"�� ����, ��� ���� ������ ��������� ���������� ����� � �����.");
	mltAboutIce2->add(L"�������� ����� ����� ����� ����� ����, �, � ���� ��, �� ������");
	mltAboutIce2->add(L"��������� ������ ���� �������� �� ���, ���� ���������� �� ���");
	mltAboutIce2->add(L"��������, �� ��� �������� ������, ������ ����������.");
	mltAboutIce2->add(L"���������� ��������� ��� ���� ��������.");
	mltAboutIce2->visible = false;
	mltAboutIce2->resize(__interface_companents::text_size::normal);

	auto *mltAboutIce3 = new __interface_companents::multiline_text(700, 340, Color::Black, Color::Yellow);
	mltAboutIce3->add(L"��� � ���������� ������ �������� ����������");
	mltAboutIce3->add(L"� ������ �� �������� �� �� ���.");
	mltAboutIce3->add(L"���������� ������� �������� �������� ������� �����������");
	mltAboutIce3->add(L"� ���� ���� ����� �����������, �� ������ �� �����.");
	mltAboutIce3->add(L"������� ����� ������ ���� ����� ����������");
	mltAboutIce3->visible = false;
	mltAboutIce3->resize(__interface_companents::text_size::normal);

	auto *mltEnd = new __interface_companents::multiline_text(700, 340, Color::Black, Color::Yellow);
	mltEnd->add(L"                                   �������!");
	mltEnd->add(L"�� ������ �������� � ������ ������ ������� � ����!");
	mltEnd->add(L"������� ������ ������ ���� ����� ����������");
	mltEnd->visible = false;
	mltEnd->resize(__interface_companents::text_size::normal);

	ObjectStatic *Castle;
	menu_pause *men;
	list<Meteor*> *Expl_list;
	list<Spearman*> *Spman = new list<Spearman*>;

	list<IceBall*> *Ice = new list<IceBall*>;

	Trigger *triggerForEnemy = new Trigger(IntRect(config->screenWidth - 500, 0, 20, config->screenHeight));

	MainWrd = new World(pointer_cast(ptr_global_memory, Image), 60, 60);

	barhp = 100;
	barmp = 100;
	HP = new __interface_companents::bar(r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), 5, 5, barhp, 0, L"HP:", Color::White, Color::Red, Color::Black); //������ ��������
	MP = new __interface_companents::bar(r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), 5, HP->getSize().left + HP->getSize().width + 5, barmp, 0, L"MP:", Color::White, Color::Blue, Color::Black);
	CameraMain = new Camera(CENTER_SCREEN_X, CENTER_SCREEN_Y, config->screenWidth, config->screenHeight);

	Castle = new ObjectStatic(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 2), 0, 0);
	Castle->sprite_rect = IntRect(0, 0, 400, 1500);
	Castle->rect_collis->setBounds(IntRect(0, 0, 400, 1500));
	//int sd = 0;
	float timer;
	//float barhp = 100;
	//flbarmp = 100;

	__interface_companents::message *message_end = new __interface_companents::message(config->screenWidth / 2, config->screenHeight / 2, r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), L"����� ��������, �� ���������", Color(38, 38, 38, 255), Color::Yellow, Color::Yellow);
	__interface_companents::message *message_settings = new __interface_companents::message(config->screenWidth / 2, config->screenHeight / 2, r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), L"��������� ������� � ���� ����� ����������� ����", Color(38, 38, 38, 255), Color::Yellow, Color::Yellow);

	menu_settings *st_men = new menu_settings(config, r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), Color::Color(38, 38, 38, 255), Color::Yellow);
	men = new menu_pause(CameraMain, r_pointer_cast(((char*)(ptr_global_memory) + block_memory_font), Font), Color::Color(38, 38, 38, 255), Color::Yellow);
	men->active = false;
	st_men->blackout_visible = false;
	Expl_list = new list<Meteor*>;

	float Second = 0;

	SoundBuffer shootBuffer; //������ ����� ��� �����
	shootBuffer.loadFromFile("Sounds/expls.ogg"); //��������� � ���� ����
	Sound expl_sound(shootBuffer); //������� ���� � ��������� � ���� ���� �� ������
	expl_sound.setVolume(volume);

	while (window->isOpen()) {

		timer = clock.getElapsedTime().asMicroseconds(); //�������� ����� � ��������
		Second = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer /= 1000;
		pos = sf::Mouse::getPosition(*window);
		realPos = window->mapPixelToCoords(pos);
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
			}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------���� � ��� ����������� �������

			if (!mlt->visible && !mltAboutHP->visible && !mltAboutMP->visible && !mltAboutEnemy->visible && !mltAboutIce->visible && !mltAboutIce2->visible && !mltAboutIce3->visible && mltEnd->visible) {
				if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && !men->active) {
					for (list<Meteor*>::iterator it_expl = Expl_list->begin(); it_expl != Expl_list->end();) {
						delete* it_expl;
						it_expl = Expl_list->erase(it_expl);
					}
					delete Expl_list;
					delete men, st_men;
					delete HP, MP;
					delete mlt, mltAboutHP, mltAboutMP, mltAboutEnemy, mltAboutEnemy, mltAboutIce, mltAboutIce2, mltAboutIce3, mltEnd, backgroundcl;
					for (list<Spearman*>::iterator it_sp = Spman->begin(); it_sp != Spman->end();) {
						delete* it_sp;
						it_sp = Spman->erase(it_sp);
					}
					for (list<IceBall*>::iterator it_ic = Ice->begin(); it_ic != Ice->end();) {
						delete* it_ic;
						it_ic = Ice->erase(it_ic);
					}
					delete Spman, Castle;
					delete triggerForEnemy;
					delete MainWrd;
					delete message_settings, message_end;
					delete CameraMain;
					return lvlnum::menuGame;
				}
			}
					
			if (!mlt->visible && !mltAboutHP->visible && !mltAboutMP->visible && !mltAboutEnemy->visible && !mltAboutIce->visible && !mltAboutIce2->visible && mltAboutIce3->visible) {
				if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && !men->active) {
					mltAboutIce3->visible = false;
					mltEnd->visible = true;	
				}
			}

			if (!mlt->visible && !mltAboutHP->visible && !mltAboutMP->visible && !mltAboutEnemy->visible && !mltAboutIce->visible && mltAboutIce2->visible) {
				if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right && !men->active) {
					if (barmp >= 100) {
						if (Ice->empty()) {
							Ice->push_back(new IceBall(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 6), realPos.x - 55, realPos.y - 65, 60));
						} else {
							Ice->back()->health = 0;
							Ice->push_back(new IceBall(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 6), realPos.x - 55, realPos.y - 65, 60));
						}
						barmp -= 100;
					}
					mltAboutIce2->visible = false;
					mltAboutIce3->visible = true;
				}
			}

			if (!mlt->visible && !mltAboutHP->visible && !mltAboutMP->visible && !mltAboutEnemy->visible && mltAboutIce->visible) {
				if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right && !men->active) {
					barmp = 100;
					if (barmp >= 100) {
						if (Ice->empty()) {
							Ice->push_back(new IceBall(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 6), realPos.x - 55, realPos.y - 65, 60));
						} else {
							Ice->back()->health = 0;
							Ice->push_back(new IceBall(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 6), realPos.x - 55, realPos.y - 65, 60));
						}
					}
					mltAboutIce->visible = false;
					mltAboutIce2->visible = true;
				}
			}
					
			if (!mlt->visible && !mltAboutHP->visible && mltAboutMP->visible) {
				if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && !men->active) {
					mltAboutMP->visible = false;
					backgroundcl->visible = false;
					EnemyActive = true;
				}
			}

			if (!mlt->visible && mltAboutHP->visible) {
				if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && !men->active) {
					mltAboutHP->visible = false;
					mltAboutMP->visible = true;
				}
			}

			if (mlt->visible) {
				if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && !men->active) {
					mlt->visible = false;
					mltAboutHP->visible = true;
				}
			}

			if (!message_end->active && !mlt->visible && !mltAboutHP->visible && !mltAboutMP->visible) {
				if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && !men->active) {
					if (barmp >= 20 && mltAboutEnemy->visible) {
						Expl_list->push_back(new Meteor(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 0), realPos.x - 200, realPos.y - 200));
					}
				}

				if (men->active && !st_men->active) {
					if (men->btContinue->isAction(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							men->active = false;
						}
					}

					if (men->btOptions->isAction(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->active = true;
						}
					}

					if (men->btExit->isAction(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							window->close();
						}
					}
				} else if (st_men->active && !message_settings->active) {
					if (st_men->btBack->isAction(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->active = false;
							st_men->backSettings(config);
						}
					}

					if (st_men->cbFullS->getSize().contains(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->cbFullS->invers();
						}
					}

					if (st_men->cbVertS->getSize().contains(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->cbVertS->invers();
						}
					}

					if (st_men->cbSound->getSize().contains(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->cbSound->invers();
						}
					}

					if (st_men->btSave->isAction(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							if (st_men->saveSettings(config) == static_cast<int>(settings_save_code::other)) {
								message_settings->active = true;
							} else {
								st_men->active = false;
							}

							window->setVerticalSyncEnabled(config->verticalSync);

							if (config->sound) {
								volume = config->soundVolume;
							} else {
								volume = 0;
							}
						}
					}

					if (st_men->combScreen->isAction(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->combScreen->next();
						} else if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right) {
							st_men->combScreen->back();
						}
					}

					if (st_men->combSoundV->isAction(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							st_men->combSoundV->next();
						} else if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right) {
							st_men->combSoundV->back();
						}
					}

				} else {
					if (message_settings->btOk->isAction(realPos.x, realPos.y)) {
						if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
							message_settings->active = false;
							st_men->active = false;
						}
					}
				}
			} else {
				if (message_end->btOk->isAction(realPos.x, realPos.y)) {
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
						for (list<Meteor*>::iterator it_expl = Expl_list->begin(); it_expl != Expl_list->end();) {
							delete* it_expl;
							it_expl = Expl_list->erase(it_expl);
						}
						delete Expl_list;
						delete men, st_men;
						delete HP, MP;
						delete mlt, mltAboutHP, mltAboutMP, mltAboutEnemy, mltAboutEnemy, mltAboutIce, mltAboutIce2, mltAboutIce3, mltEnd, backgroundcl;
						for (list<Spearman*>::iterator it_sp = Spman->begin(); it_sp != Spman->end();) {
							delete* it_sp;
							it_sp = Spman->erase(it_sp);
						}
						for (list<IceBall*>::iterator it_ic = Ice->begin(); it_ic != Ice->end();) {
							delete* it_ic;
							it_ic = Ice->erase(it_ic);
						}
						delete Spman, Castle;
						delete triggerForEnemy;
						delete MainWrd;
						delete message_settings, message_end;
						delete CameraMain;
						return lvlnum::menuGame;
					}
				}
			}

			if (window->isOpen()) { break; }
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			for (list<Meteor*>::iterator it_expl = Expl_list->begin(); it_expl != Expl_list->end();) {
				delete* it_expl;
				it_expl = Expl_list->erase(it_expl);
			}
			delete Expl_list;
			delete men, st_men;
			delete HP, MP;
			delete mlt, mltAboutHP, mltAboutMP, mltAboutEnemy, mltAboutEnemy, mltAboutIce, mltAboutIce2, mltAboutIce3, mltEnd, backgroundcl;
			for (list<Spearman*>::iterator it_sp = Spman->begin(); it_sp != Spman->end();) {
				delete* it_sp;
				it_sp = Spman->erase(it_sp);
			}
			for (list<IceBall*>::iterator it_ic = Ice->begin(); it_ic != Ice->end();) {
				delete* it_ic;
				it_ic = Ice->erase(it_ic);
			}
			delete Spman, Castle;
			delete triggerForEnemy;
			delete MainWrd;
			delete message_settings, message_end;
			delete CameraMain;
			return lvlnum::menuGame;
		}

		if (mltAboutEnemy->visible) {

			for (list<Meteor*>::iterator it = Expl_list->begin(); it != Expl_list->end();) {
						
				if ((*it)->reached_point && !(*it)->is_sound_play) {
					expl_sound.setVolume(volume);
					expl_sound.play();
					(*it)->is_sound_play = true;
				}
						
				for (list<Spearman*>::iterator it_sp = Spman->begin(); it_sp != Spman->end();) {
					if ((*it)->rect_collis->getBounds().intersects((*it_sp)->rect_collis->getBounds()) && !(*it)->cooldown) {
						expl_sound.play();
						(*it_sp)->health -= 30;
						if ((*it_sp)->health <= 0) { (*it_sp)->health = 0; }
						(*it)->cooldown = true;
					}
					it_sp++;
				}
				it++;
			}

			for (list<Spearman*>::iterator it_sp = Spman->begin(); it_sp != Spman->end();) {
				(*it_sp)->move(timer / 2, direcrion4::non);
				if ((*it_sp)->is_dead) {
					delete* it_sp;
					it_sp = Spman->erase(it_sp);
					mltAboutEnemy->visible = false;
					mltAboutIce->visible = true;
				}
				it_sp++;
			}
		}

		if (!message_end->active && !mltAboutEnemy->visible) {
			if (Keyboard::isKeyPressed(Keyboard::Escape) && !mlt->visible && !mltAboutHP->visible && !mltAboutMP->visible) { //�����
				men->active = true;
			}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------����������� ���������
			if (!men->active) {
						
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------������ ��������� ������
				for (list<Spearman*>::iterator it_sp = Spman->begin(); it_sp != Spman->end();) {
					if ((*it_sp)->is_dead) {
						delete* it_sp;
						it_sp = Spman->erase(it_sp);
					} else {
						if ((*it_sp)->rect_collis->getBounds().intersects(triggerForEnemy->getBounds())) {
							mltAboutEnemy->visible = true;
							backgroundcl->visible = true;
						}
						if ((*it_sp)->rect_collis->getBounds().intersects(Castle->rect_collis->getBounds()) && (*it_sp)->health != 0) {
							(*it_sp)->attack(timer / 2);
							if (!(*it_sp)->isCooldown(Second)) {
								barhp -= 5;
								(*it_sp)->cooldown = true;
							}
						} else {
							(*it_sp)->move(timer / 2, direcrion4::left);
						}
						it_sp++;
					}
				}

				HP->changeBar(barhp);
				HP->freeze(CameraMain, 5, 5);
				if (barhp <= 50) {
					barmp += timer / 100;
					Castle->sprite_rect = IntRect(400, 0, 400, 1500);
				} if (barhp <= 25) {
					Castle->sprite_rect = IntRect(400 * 2, 0, 400, 1500);
				} if (barhp <= 0) {
					Castle->sprite_rect = IntRect(400 * 3, 0, 400, 1500);
					barhp = 0;
					message_end->active = true;
				}
				barmp >= 100 ? barmp = 100 : barmp += timer / 100;
				MP->changeBar(barmp);
				MP->freeze(CameraMain, 5, 40);

				if (EnemyActive) { //----------------------------------------------������ � ������
					Spman->push_back(new Spearman(*(pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3), config->screenWidth + 20, config->screenHeight / 2, 45));
					EnemyActive = false;
				}	
			}
		}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------���������
		window->clear();
		MainWrd->render(*window);
				
		for (list<Spearman*>::iterator it_sp = Spman->begin(); it_sp != Spman->end();) {
			(*it_sp)->render(*window, (pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3));
			it_sp++;
		}
		Castle->render(*window, (pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 2));
		if (!mltAboutHP->visible) {
			#undef small
			HP->resize(__interface_companents::text_size::small_t);
			HP->render(*window);
			#define small char
		}
		if (!mltAboutMP->visible) {
			#undef small
			MP->resize(__interface_companents::text_size::small_t);
			MP->render(*window);
			#define small char
		}
		backgroundcl->render(*window);
		if (mltAboutHP->visible) {
			HP->resize(__interface_companents::text_size::big);
			HP->render(*window);
		}
		if (mltAboutMP->visible) {
			MP->resize(__interface_companents::text_size::big);
			MP->render(*window);
		}
		if (mltAboutEnemy->visible) {					

			for (list<Spearman*>::iterator it_sp = Spman->begin(); it_sp != Spman->end();) {
				(*it_sp)->render(*window, (pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 3));
				it_sp++;
			}
		}
		for (list<IceBall*>::iterator it_ic = Ice->begin(); it_ic != Ice->end();) {
			(*it_ic)->update(timer / 4.5);
			(*it_ic)->render(*window, (pointer_cast(((char*)(ptr_global_memory)+block_memory_sprite), Sprite) + 6));
			it_ic++;
		}
		for (list<Meteor*>::iterator it = Expl_list->begin(); it != Expl_list->end();) {
			if ((*it)->end) {
				delete* it;
				it = Expl_list->erase(it);
			} else {
				(*it)->update(timer);
				(*it)->render(*window, (pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 0), (pointer_cast(((char*)(ptr_global_memory) + block_memory_sprite), Sprite) + 1));
				it++;
			}
		}
		mltAboutHP->render(*window);
		mltAboutMP->render(*window);
		mltAboutEnemy->render(*window);
		mltAboutIce->render(*window);
		mltAboutIce2->render(*window);
		mltAboutIce3->render(*window);
		mltEnd->render(*window);

		mlt->render(*window);
		CameraMain->setView(*window);
		men->render(*window, CameraMain);
		st_men->render(*window, CameraMain);
		message_settings->render(*window, CameraMain);
		message_end->render(*window, CameraMain);
		window->display();
	}

	for (list<Meteor*>::iterator it_expl = Expl_list->begin(); it_expl != Expl_list->end();) {
		delete* it_expl;
		it_expl = Expl_list->erase(it_expl);
	}
	delete Expl_list;
	delete men, st_men;
	delete HP, MP;
	delete mlt, mltAboutHP, mltAboutMP, mltAboutEnemy, mltAboutIce, mltAboutIce2, mltAboutIce3,  mltEnd, backgroundcl;
	for (list<Spearman*>::iterator it_sp = Spman->begin(); it_sp != Spman->end();) {
		delete *it_sp;
		it_sp = Spman->erase(it_sp);
	}
	for (list<IceBall*>::iterator it_ic = Ice->begin(); it_ic != Ice->end();) {
		delete *it_ic;
		it_ic = Ice->erase(it_ic);
	}
	delete Castle, Spman;
	delete triggerForEnemy;
	delete MainWrd;
	delete message_settings, message_end;
	delete CameraMain;

	return lvlnum::exitGame;	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		
void Game::ExecuteCommand(const char* command) {
	std::string find_str(command);

	if (find_str.find("-moremana") != std::string::npos) {
		barmp_max = 99999;
		barmp = 99999;
	}

	if (find_str.find("-morehealth") != std::string::npos) {
		barhp = 99999;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Game::StartApp() {
	int out;
	out = this->Run();
	while (out != lvlnum::exitGame) {
		switch (out) {
		case lvlnum::lvlRun: out = this->LvlRun(); break;
		case lvlnum::lvlTraining: out = this->lvlTraining(); break;
		case lvlnum::menuGame: out = this->Run(); break;
		default: break;
		}
	}
}