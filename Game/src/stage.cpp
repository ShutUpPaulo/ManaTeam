/*
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include <core/environment.h>
#include <core/music.h>
#include <core/soundeffect.h> 
#include <core/audiomanager.h>
#include <core/audiomanagerwrapper.h>

#include "stage.h"
#include "item.h"
#include "map.h"
#include "player.h"
#include "player2.h"

Stage::Stage(ObjectID id)
    : Level(id)
{
    int quantidade_de_salas = 5;
    Map * maps = new Map(quantidade_de_salas);
    add_child(maps);

    Player2 *player = new Player2(this, "player", maps);
    player->set_position(600, 320);
    add_child(player);
    
    player->add_observer(this);

    Environment *env = Environment::get_instance();
    env->music->play("res/sounds/Fase1.ogg", -1);
//    env->sfx->play("res/sounds/Alarme2.ogg", 1);
}

void
Stage::draw_self()
{
    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::BLUE);   
}

bool
Stage::on_message(Object *object, MessageID id, Parameters p)
{
    if (id == Player2::hitExitDoorID)
    {
        set_next(p);
        finish();
        return true;
    }

    return false;
}
