#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <LuaBridge/LuaBridge.h>
#pragma once

//#ifndef _BASE_H_ 
//#define _BASE_H_

using namespace sf;

enum class settings_save_code {
	sound_or_sound_volume_or_verticalS = 1,
	other = 0
};

/// <summary>
/// Преобразует целочисленное значение к строке
/// </summary>
/// <param name="input">Целочисленное число</param>
/// <returns>Строка</returns>
std::string IntToStr(int input);

template<typename type>
struct axes {
	type x, y;
	axes();
	axes(type _x, type _y);
};

template<typename type>
axes<type>::axes() {
	x = 0;
	y = 0;
}

template<typename type>
axes<type>::axes(type _x, type _y) : x(_x), y(_y) {}

typedef axes<int> axes_i;
typedef axes<float> axes_f;

typedef struct settings {
	bool fullScreen;
	bool verticalSync;
	bool sound;
	unsigned int screenHeight;
	unsigned int screenWidth;
	int anisFilt;
	int textSize;
	int soundVolume;
	bool saveSettings();
	bool loadSettings();
	void createSettings(unsigned int ScreenW = 1600, unsigned int ScreenH = 900, int AnisF = 8, bool VertS = false, int TxtS = 24, bool FullS = true, bool Sound = true, int SoundV = 50);
	//1280 x 720
	//1600 x 900
	//1600 x 1200
	//1920 x 1080
	//2560 x 1440
} configuration;

//#endif 
