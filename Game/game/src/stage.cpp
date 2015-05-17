/*
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include <environment.h>

#include "stage.h"
#include "square.h"
#include "sprite.h"
#include "map.h"
#include "player.h"

Stage::Stage(ObjectID id)
    : Level(id)
{
    //Environment *env = Environment::get_instance();
    
    //double x = 0;
    //double y = env->canvas->h()*0.8;
    //double w = env->canvas->w();
    //double h = env->canvas->h();
    
    Map::room * rooms = (Map::room*) malloc (sizeof(Map::room*));
    rooms = maps.GenerateMap();
    Map::room * currentRoom = rooms;
    //m_floor.set(x, y);
    //m_floor.set_dimensions(w, h);

	map<int,Animation*> actions;
	
    actions[Sprite::IDLE] = new Animation("res/sprites/idle.png", 0, 0, 40, 81, 2,300, true);
	actions[Sprite::RUNNING] = new Animation("res/sprites/running.png", 0, 0, 40, 81, 8,50, true);
	
	
 
    Player *player = new Player(this, "player", actions);
    printf("Stage 1\n");

    player->set_position(640, 360);
    
    maps.AddObject(currentRoom, player, Map::CHAR);
    printf("adicionou\n");
    for(unsigned int it = 0; it < currentRoom->objects.size() -1 ; it++)
    {
        printf("entrou\n");
        add_child(currentRoom->objects[1]);
        printf("saiu1\n");
    }
    printf("saiu2\n");
       // add_child(player);
}

void
Stage::draw_self()
{
    const Color color {0, 200, 60 };

    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::WHITE);
    env->canvas->fill(m_floor, color);
}
