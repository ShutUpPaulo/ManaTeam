/*
 * Exemplo de um nível: a tela de uma fase.
 *
 * Autor: Edson Alves
 * Data: 29/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef STAGE_H
#define STAGE_H

#include <core/level.h>
#include <core/rect.h>

#include "map.h"
#include "room.h"

class Player;
class Map;

class Stage : public Level
{
public:
    Stage(ObjectID id, int lives, double * sanity);

    static ActionID colisionID;

private:
    Player *m_player;
    Map *m_map;
    int m_num_id;
    void draw_self();
    void update_self(unsigned long);
    double *m_sanity;

    bool on_message(Object *object, MessageID id, Parameters p);
};

#endif
