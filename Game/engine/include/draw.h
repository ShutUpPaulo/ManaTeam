#pragma once
#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>
#include "map.h"

class Draw
{
	public:
		void drawMap(Map::room*, SDL_Surface*);
};
