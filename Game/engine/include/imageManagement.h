#include <SDL/SDL.h>
#include <iostream>
#include <cstring>

using namespace std;

class ImageManagement
{
public:
	bool loadImage(char *);
	void drawImage(SDL_Surface *, const SDL_Rect *, SDL_Surface *,SDL_Rect);
};
