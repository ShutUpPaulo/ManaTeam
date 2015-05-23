#include "room.h"
#include "item.h"
#include <string>
#include <iostream>
#include <core/font.h>
#include <core/environment.h>

Room::Room(Object *parent, ObjectID id)
: Object(parent, id), r_left(nullptr), r_right(nullptr), r_top(nullptr), r_botton(nullptr)
{
	Item *piso;
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			piso = new Item(this,"piso",i*80,j*80,true);
			piso->change_sprite("res/tile_sheets/tile.png");
			piso->set_w(80);
			piso->set_h(80);
			piso->set_position(i*80,j*80);
			add_child(piso);
		}
	}
}

void Room::draw_self()
{
	Environment *env = Environment::get_instance();
	shared_ptr <Font> font = env->resources_manager->get_font("res/fonts/TakaoExGothic.ttf");
	env->canvas->set_font(font);
	env->canvas->draw(id(),300,400,Color::RED);
}

