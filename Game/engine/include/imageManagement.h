#pragma once
#include <SDL/SDL.h>
#include <iostream>
#include <cstring>

using namespace std;

class ImageManagement
{
public:
	bool loadImage(SDL_Surface *, char *);
	void drawImage(SDL_Surface *, SDL_Surface *, SDL_Rect);
};
