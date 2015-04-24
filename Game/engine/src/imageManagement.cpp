#include "imageManagement.h"
#include "game.h"

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

//Draw all the map on the screen
void ImageManagement::drawMap(Map::room * rooms, SDL_Surface *screen)
{
    if(rooms != NULL)
    {
        //Random colors hexadecimal
        uint32_t x;
        x = rand() & 0xff;
        x |= (rand() & 0xff) << 8;
        x |= (rand() & 0xff) << 16;
        x |= (rand() & 0xff) << 24;

        printf("%d\n", rooms->id);

        //
        FillRect(0, 0, 800, 600, x ,screen);
        rooms->hasMap = true;

        /*/Test
        if(rooms->id == 0)
            SDL_Flip(screen);
        SDL_Delay(1000);*/
        
        if(rooms->left != NULL)
            if(!rooms->left->hasMap)
                ImageManagement::drawMap(rooms->left, screen);
        if(rooms->right != NULL)
            if(!rooms->right->hasMap)
                ImageManagement::drawMap(rooms->right, screen);
        if(rooms->top != NULL)
            if(!rooms->top->hasMap)
                ImageManagement::drawMap(rooms->top, screen);
        if(rooms->bot != NULL)
            if(!rooms->bot->hasMap)
                ImageManagement::drawMap(rooms->bot, screen);

    }
}

void ImageManagement::drawRoom(Map::room* currentRoom, SDL_Surface* screen)
{
    //Random colors hexadecimal
    uint32_t x;
    x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;

    printf("%d\n", currentRoom->id);

    //
    FillRect(0, 0, 800, 600, x ,screen);
    currentRoom->hasMap = true;
}