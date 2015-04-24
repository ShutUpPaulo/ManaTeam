#include "menu.h"
#include "game.h"
#include "imageManagement.h"
#include <iostream>
#include <SDL/SDL_ttf.h>

Game game;

void Menu::title(SDL_Surface *screen)
{
	game.printF("ManaTeam apresenta: ", screen->w/6, screen->h/2);
	SDL_Delay(4000);

	SDL_Surface * imgTitle = SDL_LoadBMP("src/images/lena.bmp");
	
	if (!imgTitle)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return; //false;
    }
	
	//char imgName[50] = {"images/lena.bmp"};

	//imgM.loadImage(imgTitle, imgName);
	
	// centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - imgTitle ->w) / 2;
    dstrect.y = (screen->h - imgTitle->h) / 2;

	//SDL_BlitSurface(imgTitle, 0, screen, &dstrect);

	imgM.drawImage(imgTitle, screen, dstrect);
	SDL_Delay(3000);
}