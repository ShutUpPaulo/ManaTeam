/*
 * Implementação da classe que representa um jogo utilizando a SDL.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#include "game.h"
#include "map.h"
#include "draw.h"

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


using namespace std;

SDL_Surface* fontSurface;
SDL_Color fColor;
SDL_Rect fontRect;
// Create a new window
    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);
	

TTF_Font* font;

//Initialize the font, set to white
void Game::fontInit(){
        TTF_Init();
        font = TTF_OpenFont("src/font.ttf", 60);
        if(!font)
        {
            printf("Fonte nao detectada..\n\n\n");
            exit(1);
        }
        fColor.r = 255;
        fColor.g = 255;
        fColor.b = 255;
}

//Print the designated string at the specified coordinates
void Game::printF(char *c, int x, int y){
        fontSurface = TTF_RenderText_Solid(font, c, fColor);
        fontRect.x = x;
        fontRect.y = y;
        SDL_BlitSurface(fontSurface, NULL, screen, &fontRect);
        SDL_Flip(screen);
}

//Função para desenhar retangulos
void FillRect(int x, int y, int w, int h, int color, SDL_Surface *screen) {
	
    SDL_Rect rect = {x,y,w,h};
    SDL_FillRect(screen, &rect, color);
}

// Game Constructor
Game::Game()
{
    
}

// Game Destructor
Game::~Game()
{
}

int Game::run()
{

    Game::fontInit();
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);

	// Initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    
    // To make sure SDL cleans up before exit
    atexit(SDL_Quit);	
    
    
	if ( !screen )
    {
        printf("Unable to set 800x600 video: %s\n", SDL_GetError());
        return 1;
    }

    // Creating map
    Map::room * rooms = map.GenerateMap();
    Map::room * currentRoom = rooms;

    // Drawing map
    draw.drawMap(rooms, screen);

    
    
	// Program main loop
    bool done = false;

    while (not done)
    {
        update_timestep();
        runIA();
        runPhysics();
        done = update();
        done = process_input(rooms, &currentRoom, screen);
        //SDL_Delay(500);

        //Printing the room number in the screen
        char strId[5];
        sprintf(strId, "%d", currentRoom->id);
        printF(strId, screen->w/2, screen->h/2);

        if(currentRoom->top != NULL)
        {
            sprintf(strId, "%d", currentRoom->top->id);
            printF(strId, screen->w/2, screen->h/4);
        }
        if(currentRoom->bot != NULL)
        {
            sprintf(strId, "%d", currentRoom->bot->id);
            printF(strId, screen->w/2, screen->h/4 * 3);
        }
        if(currentRoom->left != NULL)
        {
            sprintf(strId, "%d", currentRoom->left->id);
            printF(strId, screen->w/4, screen->h/2);
        }
        if(currentRoom->right != NULL)
        {
            sprintf(strId, "%d", currentRoom->right->id);
            printF(strId, screen->w/4 * 3, screen->h/2);
        }
        
        SDL_Flip(screen);
    }

    return 0;
}

void Game::update_timestep()
{
}

bool Game::process_input(Map::room * rooms, Map::room ** currentRoom, SDL_Surface *screen)
{
	// Message processing loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // Check for messages
        switch (event.type)
        {
		    // Exit if the window is closed
		    case SDL_QUIT:
                printf("\nSaindo do jogo..\n\n");
                map.ResetMap(rooms);
		        return true;
		        break;

		    // Check for keypresses
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym )
                {
                    case SDLK_LEFT:
                        if((*currentRoom)->left != NULL)
                        {
                            *currentRoom = (*currentRoom)->left;
                            draw.drawRoom(*currentRoom, screen);
                        }
                        break;
                    case SDLK_RIGHT:
                        if((*currentRoom)->right != NULL)
                        {
                            *currentRoom = (*currentRoom)->right;
                            draw.drawRoom(*currentRoom, screen);
                        }
                        break;
                    case SDLK_UP:
                        if((*currentRoom)->top != NULL)
                        {
                            *currentRoom = (*currentRoom)->top;
                            draw.drawRoom(*currentRoom, screen);
                        }
                        break;
                    case SDLK_DOWN:
                        if((*currentRoom)->bot != NULL)
                        {
                            *currentRoom = (*currentRoom)->bot;
                            draw.drawRoom(*currentRoom, screen);
                        }
                        break;
                }
        }
    }
    return false;
}

void Game::runIA()
{
}

void Game::runPhysics()
{
}

bool Game::update()
{
    return false;
}

/*void Game::draw(SDL_Surface *screen)
{
	// Clear screen
    SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));
    
  	// Draw rectangle Example
  	FillRect(50,150,50,50,0xFFFFFF,screen); // White Rect
    FillRect(50+1,150+1,48,48,0x0,screen);	//Black Rect
    SDL_Flip(screen);
}*/
