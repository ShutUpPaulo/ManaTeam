/*
 * Classe que representa o jogo 7 Keys.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef TEST_H
#define TEST_H

#include <core/game.h>
 #include "player.h"

class SevenKeys : public Game
{
public:
    SevenKeys();

private:
    Level * load_level(const string& id);
    int lives;
    double sanity;
};

#endif
