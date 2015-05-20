/*
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include <core/environment.h>
#include "stage.h"
#include "item.h"
#include "map.h"
#include "player.h"

Stage::Stage(ObjectID id)
    : Level(id)
{
    Map * maps = new Map();
    add_child(maps);
//     //Environment *env = Environment::get_instance();
    
//     //double x = 0;
//     //double y = env->canvas->h()*0.8;
//     //double w = env->canvas->w();
//     //double h = env->canvas->h();
    
//     Map::room * rooms = (Map::room*) malloc (sizeof(Map::room*));
//     rooms = maps.GenerateMap();
//     Map::room * currentRoom = rooms;
//     //m_floor.set(x, y);
//     //m_floor.set_dimensions(w, h);

 	map<int,Animation*> actions;
	
     actions[Player::IDLE] = new Animation("res/sprites/idle.png", 
         0, 0, 40, 81, 2,300, true);
 	actions[Player::RUNNING] = new Animation("res/sprites/running.png", 
         0, 0, 40, 81, 8,50, true);

     Player *player = new Player(this, "player", actions);
    
//     Item *item = new Item(this, "item", 0, 0, Map::MAP, true);
    
//     item->set_x(1);
//     item->set_y(1);
    
//     printf("Stage 1\n");

     player->set_position(300, 400);
    
//     // //Adcionando objetos à sala
//     // maps.AddObject(currentRoom, player, Map::CHAR);
//     // maps.AddObject(currentRoom, item, Map::MAP);
    
//     // printf("adicionou\n");

//     // for(auto it = currentRoom->objects.begin(); 
//     //     it != currentRoom->objects.end() ; ++it)
//     // {
//     //     (*it)->set_position((*it)->x(),(*it)->y());
//     //     printf("entrou\n");
//     //     add_child((*it));
//     //     printf("saiu1\n");
//     // }
//     printf("saiu2\n");
     add_child(player);
}

void
Stage::draw_self()
{
    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::BLUE);   
}
