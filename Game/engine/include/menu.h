#pragma once

#include "imageManagement.h"

class Menu 
{
public:
	ImageManagement imgM;
	void title(SDL_Surface *);
	void mainMenu(SDL_Surface *);
};