/*
 * Classe que representa um jogo.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL/SDL.h>

void FillRect(Sint16 x, Sint16 y, Uint16 w, Uint16 h, int color, SDL_Surface *screen);

class Game
{
public:
    Game();
    ~Game();

    int run();

private:
    void update_timestep();
    bool process_input();
    void runIA();
    void runPhysics();
    bool update();
    void draw(SDL_Surface *screen);
};

#endif
