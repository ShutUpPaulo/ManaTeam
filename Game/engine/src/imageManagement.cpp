#include "imageManagement.h"


bool ImageManagement::loadImage(SDL_Surface* imgTitle, char imgName[50])
{
    if (!imgTitle)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return false;
    }
	return true;
}

void ImageManagement::drawImage(SDL_Surface* imgTitle, SDL_Surface *screen, SDL_Rect dstrect)
{
	SDL_BlitSurface(imgTitle, 0, screen, &dstrect);
	SDL_Flip(screen);
}