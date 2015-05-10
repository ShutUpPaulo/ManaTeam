/*
 * Implementação da class FrontEnd.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include <engine/environment.h>

#include "stage.h"
#include "square.h"
#include "sprite.h"

Stage::Stage(ObjectID id)
    : Level(id)
{
    Environment *env = Environment::get_instance();

    double x = 0;
    double y = env->canvas->h()*0.8;
    double w = env->canvas->w();
    double h = env->canvas->h();

    m_floor.set(x, y);
    m_floor.set_dimensions(w, h);

	map<int,Animation*> actions;
    actions[Sprite::IDLE] = new Animation("res/sprites/player.png", 0, 0, 54, 129, 12,300, true);
	actions[Sprite::RUNNING] = new Animation("res/sprites/player.png", 0, 0, 54, 129, 12,300, true);
	
    Sprite *sprite = new Sprite(this, "sprite",actions);
    
    printf("Stage 1\n");

	x -= sprite->w();
    y -= sprite->h();

    sprite->set_position(x, y);

    add_child(sprite);
}

void
Stage::draw_self()
{
    const Color color {0, 200, 60 };

    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::WHITE);
    env->canvas->fill(m_floor, color);
}
