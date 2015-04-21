#include <SDL/SDL.h>
#include <iostream>

class ImageManagement()
{
public:
	bool loadImage(String);
	void drawImage(SDL_Surface *, const SDL_Rect *, SDL_Surface *,SDL_Rect *);
};
