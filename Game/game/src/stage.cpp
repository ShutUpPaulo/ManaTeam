/*
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include <core/environment.h>
#include <core/music.h>
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

 	/*map<int,Animation*> actions;
	
    actions[Player::IDLE] = new Animation("res/sprites/idle.png", 
         0, 0, 40, 81, 2,300, true);
 	actions[Player::RUNNING] = new Animation("res/sprites/running.png", 
         0, 0, 40, 81, 8,50, true);*/

     /*Player *player = new Player(this, "player", actions, maps);

     player->set_position(600, 320);

     add_child(player);*/

    

    Player2 *player = new Player2(this, "player", maps);
    player->set_position(600, 320);
    add_child(player);

   AudioManagerWrapper();
    AudioManagerMusic * music2 = new AudioManagerMusic();
 //   Mix_Music * musica = Mix_LoadMUS("res/sounds/MusicaMenu.ogg");
   // Music * song = new Music (musica);
    music2 -> play("res/sounds/Fase1.ogg", -1);


}

void
Stage::draw_self()
{
    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::BLUE);   
}
