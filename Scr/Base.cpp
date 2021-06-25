#include "Base.hpp"

std::string IntToStr(int input) {
	std::ostringstream output;
	output << input;
	return output.str();
}

//----------------------------------Настройки-Settings-Начало------------------------------
void settings::createSettings(unsigned int ScreenW, unsigned int ScreenH, int AnisF, bool VertS, int TxtS, bool FullS, bool Sound, int SoundV) {
	fullScreen = FullS;
	verticalSync = VertS;
	screenHeight = ScreenH;
	screenWidth = ScreenW;
	anisFilt = AnisF;
	textSize = TxtS;
	sound = Sound;
	soundVolume = SoundV;
}

bool settings::saveSettings() {
	std::ofstream zap;
	zap.open("settings.lua");
	zap << "fullScreen = " << (fullScreen ? "true" : "false") << "\n";
	zap << "verticalSync = " << (verticalSync ? "true" : "false") << "\n";
	zap << "screenHeight = " << screenHeight << "\n";
	zap << "screenWidth = " << screenWidth << "\n";
	zap << "anisFilt = " << anisFilt << "\n";
	zap << "textSize = " << textSize << "\n";
	zap << "sound = " << (sound ? "true" : "false") << "\n";
	zap << "soundVolume = " << soundVolume << "\n";
	zap.close();
	return true;
}

bool settings::loadSettings() {
	lua_State* L = luaL_newstate(); //Создаем объект lua, из которого будем получать данные

	if (luaL_loadfile(L, "settings.lua") || lua_pcall(L, 0, 0, 0)) { //Если файл не найден
		return false;
	} else {
		luaL_openlibs(L); //Загружаем библиотеку для работы с lua файлами

		fullScreen = luabridge::getGlobal(L, "fullScreen").cast<bool>();

		verticalSync = luabridge::getGlobal(L, "verticalSync").cast<bool>();

		screenHeight = luabridge::getGlobal(L, "screenHeight").cast<int>();

		screenWidth = luabridge::getGlobal(L, "screenWidth").cast<int>();

		anisFilt = luabridge::getGlobal(L, "anisFilt").cast<int>();

		textSize = luabridge::getGlobal(L, "textSize").cast<int>();

		sound = luabridge::getGlobal(L, "sound").cast<bool>();

		soundVolume = luabridge::getGlobal(L, "soundVolume").cast<int>();
	}
	return true;
}
//----------------------------------Настройки-Settings-Конец-------------------------------