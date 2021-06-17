#include "Game.hpp"

int main(int argc, char* argv[]){
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

	Game* gamez = nullptr;
	gamez = new Game();

	if (argc >= 2) { //Проверяем наличие ключей запуска
		for (int i = 1; argc > i; i++) {
			gamez->ExecuteCommand(argv[i]);
		}
	}
	gamez->StartApp(); //Запускаем приложение
	delete gamez;

	return 0;
}