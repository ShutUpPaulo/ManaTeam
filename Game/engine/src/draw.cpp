#include "draw.h"
#include "game.h"
#include <stdio.h>
using namespace std;

void Draw::drawMap(Map::room * rooms, SDL_Surface *screen)
{
    if(rooms != NULL)
    {
        uint32_t x;
        x = rand() & 0xff;
        x |= (rand() & 0xff) << 8;
        x |= (rand() & 0xff) << 16;
        x |= (rand() & 0xff) << 24;

        printf("%d\n", rooms->id);
        FillRect(0, 0, 800, 600, x ,screen);
        rooms->hasMap = true;
        SDL_Flip(screen);

        SDL_Delay(1000);
        if(rooms->left != NULL)
            if(!rooms->left->hasMap)
                Draw::drawMap(rooms->left, screen);
        if(rooms->right != NULL)
            if(!rooms->right->hasMap)
                Draw::drawMap(rooms->right, screen);
        if(rooms->top != NULL)
            if(!rooms->top->hasMap)
                Draw::drawMap(rooms->top, screen);
        if(rooms->bot != NULL)
            if(!rooms->bot->hasMap)
                Draw::drawMap(rooms->bot, screen);

    }
}