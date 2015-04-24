#pragma once
#include <SDL/SDL.h>
#include "map.h"

using namespace std;

class ImageManagement
{
	public:
		bool loadImage(SDL_Surface *, char *);
		void drawImage(SDL_Surface *, SDL_Surface *, SDL_Rect);
		void drawMap(Map::room*, SDL_Surface*);
		void drawRoom(Map::room*, SDL_Surface*);
};
