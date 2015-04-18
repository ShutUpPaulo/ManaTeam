#include "draw.h"
#include "game.h"
#include <stdio.h>
using namespace std;

//Draw all the map on the screen
void Draw::drawMap(Map::room * rooms, SDL_Surface *screen)
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

void Draw::drawRoom(Map::room* currentRoom, SDL_Surface* screen)
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