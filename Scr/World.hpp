#include "Base.hpp"
#pragma once

//#ifndef _WORLD_H_
//#define _WORLD_H_


#pragma	pack(push, 1)
class World {
	private:
		int size_x, size_y;
		Texture* worldTexture;
		Sprite* worldSpr;
		sf::String* mass_sp;
	public:
		World(Image* ptr_on_img, int X_SIZE, int Y_SIZE);
		~World() noexcept;
		void render(RenderWindow& wd) noexcept;
};
#pragma	pack(pop)

//#endif 
