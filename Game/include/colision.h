#ifndef COLISION_H
#define COLISION_H

#include <core/rect.h>

#include "item.h"
#include "player.h"

class Player;
class Map;

class Colision : public Object
{
public:

    static ActionID colisionID;

    verify_colision(Object* item1, Object* item2);
    verify_colision(Player* m_player, Object* item);

private:
};

#endif
